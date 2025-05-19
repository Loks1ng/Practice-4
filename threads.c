#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Структура для передачи данных в поток
typedef struct {
    int thread_num;
    int sleep_time;
} thread_data;

// Функция, выполняемая в потоке
void* thread_function(void* arg) {
    thread_data* data = (thread_data*)arg;
    
    printf("%d-й поток начал работу (время работы: %d сек)\n", 
           data->thread_num, data->sleep_time);
    
    // Имитация работы потока
    sleep(data->sleep_time);
    
    printf("%d-й поток выполнил задачу\n", data->thread_num);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data thread_data_array[NUM_THREADS];
    int rc;
    char choice;
    
    do {
        // Запрос времени работы для каждого потока
        for (int i = 0; i < NUM_THREADS; i++) {
            printf("Введите время работы для потока %d (в секундах): ", i+1);
            scanf("%d", &thread_data_array[i].sleep_time);
            thread_data_array[i].thread_num = i+1;
        }
        
        // Создание потоков
        for (int i = 0; i < NUM_THREADS; i++) {
            rc = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data_array[i]);
            if (rc) {
                printf("Ошибка: невозможно создать поток %d, код ошибки: %d\n", i+1, rc);
                exit(-1);
            }
        }
        
        // Ожидание завершения всех потоков
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        
        // Запрос на повторение или выход
        printf("\nВсе потоки завершили работу.\n");
        printf("Нажмите 'x' чтобы выйти, или 'r' чтобы перезапустить: ");
        scanf(" %c", &choice);
        
    } while (choice == 'r' || choice == 'R');
    
    printf("Программа завершена.\n");
    return 0;
}
