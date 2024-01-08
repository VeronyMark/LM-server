#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include "buffer.h"
#include "pos_sockets/char_buffer.h"
#include "pos_sockets/active_socket.h"
#include "pos_sockets/passive_socket.h"
#include "Simulacia.h"

typedef struct sprava {
    long long row;
    long long column;
    long long numberAnts;
    long long numberSteps;
    long long type;
    long long logic;
    long long solutions;
} SPRAVA;


;

typedef struct SimulaciaC SimulaciaC;

_Bool try_deserializate(struct sprava* pi_estimation, struct char_buffer* buf) {
    //ocakavam ze to takto pride

    if (sscanf(buf->data, "%lld;%lld;%lld;%lld;%lld;%lld;%lld",
               &pi_estimation->row,
               &pi_estimation->column,
               &pi_estimation->numberAnts,
               &pi_estimation->numberSteps,
               &pi_estimation->type,
               &pi_estimation->logic,
               &pi_estimation->solutions) == 7) {
        /* printf("ROW %lld \n", pi_estimation->row);
         printf("COLUMN %lld\n", pi_estimation->column);

         printf("ANTS %lld\n", pi_estimation->numberAnts);

         printf("numberSteps %lld\n", pi_estimation->numberSteps);

         printf("type %lld\n", pi_estimation->type);
         printf("logic %lld\n", pi_estimation->logic);
         printf("solutions %lld\n", pi_estimation->solutions);
 */
        struct Simulacia s;
        simuluj(&s,  pi_estimation->row,  pi_estimation->column,  pi_estimation->numberAnts,  pi_estimation->numberSteps,  pi_estimation->type,  pi_estimation->logic,  pi_estimation->solutions);

        return true;
    }


    return false;
}

GENERATE_BUFFER(struct sprava, sprava)


typedef struct thread_data {
    long long replications_count;
    struct buffer_sprava buf;
    pthread_mutex_t mutex;
    pthread_cond_t is_full;
    pthread_cond_t is_empty;

    short port;
    ACTIVE_SOCKET* my_socket;
} THREAD_DATA;

void thread_data_init(struct thread_data* data, int buffer_capacity,
                      short port, ACTIVE_SOCKET* my_socket) {
    buffer_sprava_init(&data->buf, buffer_capacity);
    pthread_mutex_init(&data->mutex, NULL);
    pthread_cond_init(&data->is_full, NULL);
    pthread_cond_init(&data->is_empty, NULL);

    data->port = port;
    data->my_socket = my_socket;
}

void thread_data_destroy(struct thread_data* data) {
    data->replications_count = 0;
    buffer_sprava_destroy(&data->buf);
    pthread_mutex_destroy(&data->mutex);
    pthread_cond_destroy(&data->is_full);
    pthread_cond_destroy(&data->is_empty);

    data->port = 0;
    data->my_socket = NULL;
}

/*
 * klient musi byt schopny sa ku mne pripojit spravim pasivny socket
 *
 *
 * ak 3 klientov pre kazdeho samostatne vlakno v kazdom samostatne bezi operacia start reading
 * vzdy s inym socketom so socketom ktr predstavuje samostatneho klienta
 *
 *
 * ak potrebujem samostatne ziskavat data
 */
void* process_client_data(void* thread_data) {
    struct thread_data* data = (struct thread_data*)thread_data;

    PASSIVE_SOCKET  sock;
    passive_socket_init(&sock);

    //   printf("VZNIKA SOCKEt");
    //     vznikol aktivny socket                                     pocuva na tomto porte
    passive_socket_start_listening(&sock, data->port);
    //kvazi zablokovane kym sa nejaky klient nepripoji
    //v data-> my socket  bude aktivny klienkt ktr sa ku mne pripoji

    passive_socket_wait_for_client(&sock, data->my_socket);
    //ked sa ku mne pripojil tak uz konci
    //ak by som chcel 3 klientov -> 3krat volam wait_for_client

    // while passive_socket_is_listening() --> mozne pouzitie
    // printf("zacina pocuvat");

    passive_socket_stop_listening(&sock);
    // printf("prestava pocuvat");
    active_socket_start_reading(data->my_socket);

    passive_socket_destroy(&sock);


    //v tomto vlakne prebieha citanie dat -> spracovava
    //bezi to "donekonecna"

    //*

    //*
    return NULL;
}

/*void* produce(void* thread_data) {
    struct thread_data* data = (struct thread_data*)thread_data;

    for (long long i = 1; i <= data->replications_count; ++i) {
        POINT item = generate_point();

        pthread_mutex_lock(&data->mutex);
        while (!buffer_point_try_push(&data->buf, item)) {
            pthread_cond_wait(&data->is_empty, &data->mutex);
        }
        pthread_cond_signal(&data->is_full);
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}
*/

_Bool try_get_client_sprava(struct active_socket* my_sock, struct sprava* client_pi_estimaton) {
//citanie dat so socketu -> buffer potrebujem
    CHAR_BUFFER  buf;
    char_buffer_init(&buf);

    _Bool result = false;

    //nad aktivnych socket skusi do premennej buf
    //dostanem spravu ktr mozem dalej spracovat
    //ak vrati false nemam tam ziadnu spravu -> nic neurobim
    if(active_socket_try_get_read_data(my_sock,&buf)) {
        //printf(buf.data);
        // printf(&buf);
        //deserializacia retazec na formu ktr treba
        //ak uspesne tak sa ulozi ak neuspesne kontrola ci to nebola koncova sprva
        if(!try_deserializate(client_pi_estimaton, &buf)) {
            //ak koncova sprava
            if(active_socket_is_end_message(my_sock, &buf)) {
                //ukoncenie -> uz uplne
                active_socket_stop_reading(my_sock);
                //zavolanim stop reading sa to v process_client_data odblokuje
                //konci metoda process client data
            }
        } else {
            result = true;
        }
    }


    ///TODO
    active_socket_write_data(&my_sock,"end");

    char_buffer_destroy(&buf);
    return result;
}

void* consume(void* thread_data) {

    struct thread_data *data = (struct thread_data *) thread_data;
    printf("ZACINA SA KOMUNIKACIA");

    struct sprava clientSprava;


    if (data->my_socket != NULL) {
        try_get_client_sprava(data->my_socket, &clientSprava);
        printf("UKONCUJEME");
        ///
        char responseMessage[] = "koniec bejby response";

        //active_socket_write_data(data->my_socket, responseMessage);
        //active_socket_write_end_message(data->my_socket);
    }
    if (data->my_socket == NULL) {
        // active_socket_write_data(data->my_socket,"koniec bejby" );
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    //  pthread_t th_produce;
    pthread_t th_receive;

    struct thread_data data;

    //musim mat activny socket
    struct active_socket my_socket;
//inicialia -> konkretne pripravena pamat
    active_socket_init(&my_socket);

    // do thread data pribudne parameter -> aktivny socker
    thread_data_init(&data, 7, 14000, &my_socket);

    //nastartujem vlakna -> 1)producent
    //  pthread_create(&th_produce, NULL, consume, &data);

    //na zisk dat z klientskej strany -> speci proces client_data  citanie dat zo soketu
    pthread_create(&th_receive, NULL, process_client_data, &data);

    //v hlavnom vlakne spustim konzumenta

    pthread_join(th_receive, NULL);

    consume(&data);
//send

    //join vlakien

    thread_data_destroy(&data);
    active_socket_destroy(&my_socket);

    return 0;
}