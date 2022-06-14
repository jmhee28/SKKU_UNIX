#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int circle_count = 0;
int num_threads;
int num_per_thread;
pthread_mutex_t m;

double rand_double() {
	return random() / (double)RAND_MAX;
}

void *monte(void *arg) {
	int point_in_circle = 0;
	int id = *((int *)arg);
	double x, y;

	for(int i = 0; i < id; i++) {
		x = rand_double();
		y = rand_double();
		if(x*x + y*y < 1.0)
			point_in_circle += 1;
	}

	pthread_mutex_lock(&m);
	circle_count += point_in_circle;
	pthread_mutex_unlock(&m);

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	num_threads = atoi(argv[1]);
	num_per_thread = atoi(argv[2]);
	double pi;

	pthread_t tid[num_threads];
	pthread_mutex_init(&m, NULL);
	srandom((unsigned)time(NULL));

	for(int i = 0; i < num_threads; i++)
		pthread_create(&tid[i], 0, monte, &num_per_thread);
	for(int i = 0; i < num_threads; i++)
		pthread_join(tid[i], NULL);
	
	pi = 4.0 * circle_count / (num_per_thread * num_threads);
	printf("%lf\n", pi);

	return 0;	
}
