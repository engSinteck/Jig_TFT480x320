#include "ff.h"  // FATFS headers
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// Buffer para leitura
#define BUFFER_SIZE 4096  // 4KB - tamanho comum de cluster
static uint8_t read_buffer[BUFFER_SIZE];

// Função para criar arquivo de teste de 1MB (se não existir)
FRESULT create_test_file(const char* filename)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    UINT bytes_written;
    uint32_t total_written = 0;
    const uint32_t file_size = 1 * 1024 * 1024;  // 1MB
    uint8_t pattern = 0xAA;
    
    // Monta o sistema de arquivos
    res = f_mount(&fs, "0:", 1);
    if (res != FR_OK) {
        printf("Erro ao montar FATFS: %d\n", res);
        return res;
    }
    
    // Verifica se o arquivo já existe
    res = f_open(&file, filename, FA_READ);
    if (res == FR_OK) {
        f_close(&file);
        printf("Arquivo já existe: %s\n", filename);
        return FR_OK;
    }
    
    // Cria o arquivo de teste
    printf("Criando arquivo de teste: %s (1MB)...\n", filename);
    res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
        printf("Erro ao criar arquivo: %d\n", res);
        return res;
    }
    
    // Preenche o buffer com padrão
    memset(read_buffer, pattern, BUFFER_SIZE);
    
    // Escreve 1MB (256 blocos de 4KB)
    while (total_written < file_size) {
        uint32_t remaining = file_size - total_written;
        uint32_t write_size = (remaining < BUFFER_SIZE) ? remaining : BUFFER_SIZE;
        
        res = f_write(&file, read_buffer, write_size, &bytes_written);
        if (res != FR_OK || bytes_written != write_size) {
            printf("Erro na escrita: %d\n", res);
            f_close(&file);
            return res;
        }
        
        total_written += bytes_written;
        
        // Muda o padrão a cada bloco (opcional - para verificar integridade)
        pattern++;
        memset(read_buffer, pattern, BUFFER_SIZE);
    }
    
    f_close(&file);
    printf("Arquivo criado com sucesso: %s (%lu bytes)\n", filename, total_written);
    return FR_OK;
}

// Função para testar velocidade de leitura
FRESULT speed_test_read(const char* filename) {
    FATFS fs;
    FIL file;
    FRESULT res;
    UINT bytes_read;
    uint32_t total_read = 0;
    uint32_t file_size = 0;
    uint32_t start_time, end_time;
    float elapsed_ms, speed_kb_s, speed_mb_s;
    
    // Monta o sistema de arquivos
    res = f_mount(&fs, "0:", 1);
    if (res != FR_OK) {
        printf("Erro ao montar FATFS: %d\n", res);
        return res;
    }
    
    // Abre o arquivo para leitura
    res = f_open(&file, filename, FA_READ);
    if (res != FR_OK) {
        printf("Erro ao abrir arquivo: %d\n", res);
        return res;
    }
    
    // Obtém o tamanho do arquivo
    file_size = f_size(&file);
    printf("Tamanho do arquivo: %lu bytes (%.2f MB)\n", file_size, file_size / (1024.0f * 1024.0f));
    
    printf("\nIniciando teste de leitura...\n");
    printf("Buffer size: %d bytes\n", BUFFER_SIZE);
    printf("Lendo em blocos de %d bytes...\n\n", BUFFER_SIZE);
    
    // Marca o tempo inicial
    start_time = HAL_GetTick();
    
    // Lê o arquivo em blocos
    uint32_t block_count = 0;
    do {
        res = f_read(&file, read_buffer, BUFFER_SIZE, &bytes_read);
        if (res != FR_OK) {
            printf("Erro na leitura: %d\n", res);
            f_close(&file);
            return res;
        }
        
        total_read += bytes_read;
        block_count++;
        
        // Opcional: verifica integridade dos dados (útil para testes)
        // verify_buffer(read_buffer, bytes_read);
        
    } while (bytes_read > 0);
    
    // Marca o tempo final
    end_time = HAL_GetTick();
    
    // Fecha o arquivo
    f_close(&file);
    
    // Calcula estatísticas
    elapsed_ms = (float)(end_time - start_time);
    
    if (elapsed_ms > 0) {
        speed_kb_s = (total_read / 1024.0f) / (elapsed_ms / 1000.0f);
        speed_mb_s = speed_kb_s / 1024.0f;
    } else {
        speed_kb_s = 0;
        speed_mb_s = 0;
    }
    
    // Exibe resultados
    printf("\n========== RESULTADOS ==========\n");
    printf("Total lido: %lu bytes (%.2f KB)\n", total_read, total_read / 1024.0f);
    printf("Blocos lidos: %lu\n", block_count);
    printf("Tempo total: %.2f ms\n", elapsed_ms);
    printf("Velocidade: %.2f KB/s\n", speed_kb_s);
    printf("Velocidade: %.2f MB/s\n", speed_mb_s);
    printf("================================\n");
    
    return FR_OK;
}

// Função para testar leitura com diferentes tamanhos de buffer
void speed_test_multiple_buffers(const char* filename) {
    const uint32_t buffer_sizes[] = {64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    const int num_tests = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    
    printf("\n=== TESTE DE LEITURA COM DIFERENTES BUFFERS ===\n");
    
    for (int i = 0; i < num_tests; i++) {
        printf("\n--- Buffer: %ld bytes ---\n", buffer_sizes[i]);
        
        // Temporariamente muda o tamanho do buffer
//        uint32_t original_buffer_size = BUFFER_SIZE;
        // Como BUFFER_SIZE é constante, usamos um buffer dinâmico
        uint8_t* dynamic_buffer = (uint8_t*)malloc(buffer_sizes[i]);
        if (dynamic_buffer == NULL) {
            printf("Falha ao alocar buffer de %ld bytes\n", buffer_sizes[i]);
            continue;
        }
        
        FATFS fs;
        FIL file;
        FRESULT res;
        UINT bytes_read;
        uint32_t total_read = 0;
        uint32_t start_time, end_time;
        
        f_mount(&fs, "0:", 1);
        res = f_open(&file, filename, FA_READ);
        if (res != FR_OK) {
            printf("Erro ao abrir arquivo: %d\n", res);
            free(dynamic_buffer);
            continue;
        }
        
        start_time = HAL_GetTick();
        
        do {
            res = f_read(&file, dynamic_buffer, buffer_sizes[i], &bytes_read);
            if (res != FR_OK) {
                printf("Erro na leitura: %d\n", res);
                break;
            }
            total_read += bytes_read;
        } while (bytes_read > 0);
        
        end_time = HAL_GetTick();
        f_close(&file);
        
        float elapsed_ms = (float)(end_time - start_time);
        float speed_kb_s = (total_read / 1024.0f) / (elapsed_ms / 1000.0f);
        
        printf("Tempo: %.2f ms | Velocidade: %.2f KB/s (%.2f MB/s)\n", 
               elapsed_ms, speed_kb_s, speed_kb_s / 1024.0f);
        
        free(dynamic_buffer);
    }
}

// Função para verificar integridade dos dados lidos
int verify_buffer(const uint8_t* buffer, uint32_t size) {
    // Verifica se o buffer tem dados válidos
    // (Implementação simples - pode ser expandida)
    for (uint32_t i = 0; i < size; i++) {
        if (buffer[i] == 0x00) {
            // Dados zerados podem indicar erro
            return 0;
        }
    }
    return 1;
}

// Função para testar leitura sequencial vs aleatória
FRESULT test_random_read(const char* filename) {
    FATFS fs;
    FIL file;
    FRESULT res;
    UINT bytes_read;
    uint32_t file_size;
    uint32_t positions[10] = {0, 100*1024, 200*1024, 300*1024, 400*1024, 
                             500*1024, 600*1024, 700*1024, 800*1024, 900*1024};
    uint32_t start_time, end_time;
    uint8_t buffer[512];
    
    f_mount(&fs, "0:", 1);
    res = f_open(&file, filename, FA_READ);
    if (res != FR_OK) return res;
    
    file_size = f_size(&file);
    printf("\n=== TESTE DE LEITURA ALEATORIA ===\n");
    printf("Arquivo: %s (%lu bytes)\n", filename, file_size);
    
    start_time = HAL_GetTick();
    
    for (int i = 0; i < 10; i++) {
        if (positions[i] < file_size) {
            // Move para posição específica
            res = f_lseek(&file, positions[i]);
            if (res != FR_OK) {
                printf("Erro no seek para posicao %lu: %d\n", positions[i], res);
                break;
            }
            
            // Lê 512 bytes
            res = f_read(&file, buffer, sizeof(buffer), &bytes_read);
            if (res != FR_OK) {
                printf("Erro na leitura: %d\n", res);
                break;
            }
            
            printf("Posicao %lu: lidos %u bytes\n", positions[i], bytes_read);
        }
    }
    
    end_time = HAL_GetTick();
    f_close(&file);
    
    float elapsed_ms = (float)(end_time - start_time);
    printf("Tempo total de seeks/reads: %.2f ms\n", elapsed_ms);
    
    return FR_OK;
}


// Função principal de exemplo
int Test_FATFS(void)
{
    const char* test_file = "TELA_FUNDO_MAIN.bin";
	//const char* test_file = "speed_test.bin";
    
    printf("=== TESTE DE VELOCIDADE DE LEITURA FATFS ===\n\n");
    
//    // 1. Cria o arquivo de teste se não existir
//    FRESULT res = create_test_file(test_file);
//    if (res != FR_OK) {
//        printf("Falha ao criar arquivo de teste\n");
//        return -1;
//    }
    
    // 2. Teste de leitura com buffer padrão (4KB)
    FRESULT res = speed_test_read(test_file);
    if (res != FR_OK) {
        printf("Falha no teste de leitura\n");
        return -1;
    }
    
    // 3. Teste com diferentes tamanhos de buffer
    speed_test_multiple_buffers(test_file);
    
    // 4. Teste de leitura aleatória
    test_random_read(test_file);
    
    return 0;
}
