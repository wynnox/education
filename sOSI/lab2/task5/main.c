#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int max_people;

pthread_mutex_t mutex;
int count_bathroom = 0;
int count_male = 0;
int count_female = 0;
int is_male_in_bathroom = 0;

void male_enter() {
    pthread_mutex_lock(&mutex);
    while ((count_bathroom == max_people) || (count_female > 0) || (is_male_in_bathroom && (count_male == max_people)))
    {
        pthread_mutex_unlock(&mutex);
        usleep(100);
        pthread_mutex_lock(&mutex);
    }

    is_male_in_bathroom = 1;
    count_bathroom++;
    count_male++;

    printf("-> Man entered the bathroom\n");
    printf("\nBathroom is for MEN now\n");
    printf("    People in bathroom = %d (Man: %d, Woman: %d)\n", count_bathroom, count_male, count_female);

    pthread_mutex_unlock(&mutex);
}

void male_leave() {
    pthread_mutex_lock(&mutex);

    count_bathroom--;
    count_male--;

    printf("<- One man left the bathroom\n");
    printf("    People in bathroom = %d (Man: %d, Woman: %d)\n", count_bathroom, count_male, count_female);

    if (count_male == 0)
    {
        is_male_in_bathroom = 0;
    }

    pthread_mutex_unlock(&mutex);
}

void* get_man_thread(void* arg)
{
    const int man_count = *((int*)arg);
    for (int i = 0; i < man_count; i++)
    {
        male_enter();
        sleep(rand() % 5);
        male_leave();
    }
    return NULL;
}

void female_leave()
{
    pthread_mutex_lock(&mutex);

    count_bathroom--;
    count_female--;

    printf("<- One woman left the bathroom\n");
    printf("    People in bathroom = %d (Man: %d, Woman: %d)\n", count_bathroom, count_male, count_female);

    pthread_mutex_unlock(&mutex);
}

void female_enter()
{
    pthread_mutex_lock(&mutex);
    while ((count_bathroom == max_people) || (count_male > 0))
    {
        pthread_mutex_unlock(&mutex);
        usleep(100);
        pthread_mutex_lock(&mutex);
    }

    count_bathroom++;
    count_female++;

    printf("-> Woman entered the bathroom\n");
    printf("\nBathroom is for WOMEN now\n");
    printf("    People in bathroom = %d (Man: %d, Woman: %d)\n", count_bathroom, count_male, count_female);

    pthread_mutex_unlock(&mutex);
}

void* get_woman_thread(void* arg)
{
    const int woman_count = *((int*)arg);
    for (int i = 0; i < woman_count; i++)
    {
        female_enter();
        sleep(rand() % 5);
        female_leave();
    }
    return NULL;
}

void bath_solution(int count_man, int count_woman)
{
    pthread_t male[count_man];
    pthread_t female[count_woman];

    for (int i = 0; i < count_man; i++)
    {
        pthread_create(&male[i], NULL, get_man_thread, &count_man);
    }

    for (int i = 0; i < count_woman; i++)
    {
        pthread_create(&female[i], NULL, get_woman_thread, &count_woman);
    }

    for (int i = 0; i < count_man; i++)
    {
        pthread_join(male[i], NULL);
    }

    for (int i = 0; i < count_woman; i++)
    {
        pthread_join(female[i], NULL);
    }
}

int main(int argc, char * argv[]) 
{
    if(argc != 2) 
    {
        printf("no");
        return 1;
    }

    max_people = atoi(argv[1]);

    int count_man, count_woman;
    printf("Enter number of men: ");
    scanf("%d", &count_man);
    printf("Enter number of women: ");
    scanf("%d", &count_woman);

    pthread_mutex_init(&mutex, NULL);

    bath_solution(count_man, count_woman);

    pthread_mutex_destroy(&mutex);

    return 0;
}
