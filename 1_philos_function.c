
#include "philo.h"

long long find_time(long long start_time)
{
    struct timeval	tv;
    long long time;

    gettimeofday(&tv, NULL);
    if(start_time != -1)
        time = tv.tv_sec * 1000LL + tv.tv_usec / 1000 - start_time;
    else
        time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return (time);
}

int f_dead_cntrl(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->mutex_dead_cntrl);
    if (philo->args->dead_cntrl == 1)
    {
        pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);
        return (1);
        //return ((void *)(-1));
    }
    pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);
    return (0);
}

void *philos_function(void *arg)
{
    t_philo *philo;
    long long start_time;
    long long take_fork;
    long long before_fork;

    philo = (t_philo *)arg;
    start_time = find_time(-1);
    if(philo->args->number_of_philosophers == 1)
    {
        printf("time: %d, %d took the fork\n", 0, philo->philo_id);
        printf("time: %d, %d philo died2!\n", philo->args->time_to_die, philo->philo_id);
        return ((void *)(-1));
    }
    while(1)
    {
        if(f_dead_cntrl(philo))
            return ((void *)(-1));
        if (philo->args->number_of_times_must_eat != -1 && 
                philo->eat_times >= philo->args->number_of_times_must_eat)
            return ((void *)(-1));
        //çatal almadan önce;
        before_fork = find_time (start_time);
        if (philo->philo_id % 2 != 0)
        {
            pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
            pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
        }
        else
        {
            pthread_mutex_lock(&philo->fork_mutex[philo->right_fork_id]);
            pthread_mutex_lock(&philo->fork_mutex[philo->left_fork_id]);
        }
        //çatal aldıktan sonra
        take_fork = find_time(start_time);
        // if(f_dead_cntrl(philo))
        //    return ((void *)(-1));
        if(take_fork - before_fork >= philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died3!\n", before_fork + philo->args->time_to_die, philo->philo_id);
            pthread_mutex_lock(&philo->args->mutex_dead_cntrl);
            philo->args->dead_cntrl = 1;
            pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);//
            return ((void *)(-1));
        }
        //  if(f_dead_cntrl(philo))
        //     return ((void *)(-1));
        printf("time: %lld, %d took fork\n", take_fork, philo->philo_id);
        printf("time: %lld, %d took fork\n", take_fork, philo->philo_id);
        printf("time: %lld, %d philo eating\n", take_fork, philo->philo_id);
        //  if(f_dead_cntrl(philo))
        //     return ((void *)(-1));
        if(philo->args->time_to_eat > philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died4!\n", take_fork + philo->args->time_to_die, philo->philo_id);
            pthread_mutex_lock(&philo->args->mutex_dead_cntrl);
            philo->args->dead_cntrl = 1;
            pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);//
            return ((void *)(-1));
        }
        usleep(philo->args->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->fork_mutex[philo->right_fork_id]);
        pthread_mutex_unlock(&philo->fork_mutex[philo->left_fork_id]);

        //  if(f_dead_cntrl(philo))
        //     return ((void *)(-1));
        printf("time: %lld, %d philo sleeping\n", take_fork + philo->args->time_to_eat, philo->philo_id);
        //  if(f_dead_cntrl(philo))
        //     return ((void *)(-1));
        if(philo->args->time_to_sleep > philo->args->time_to_die)
        {
            printf("time: %lld, %d philo died5!\n", take_fork + philo->args->time_to_eat + philo->args->time_to_die, philo->philo_id);
            pthread_mutex_lock(&philo->args->mutex_dead_cntrl);
            philo->args->dead_cntrl = 1;
            pthread_mutex_unlock(&philo->args->mutex_dead_cntrl);//
            return ((void *)(-1));;
        }
        usleep(philo->args->time_to_sleep * 1000);
    }
    return ((void *)(0));
}