#ifndef SOCKETS_SERVER_ACTIVE_SOCKET_H
#define SOCKETS_SERVER_ACTIVE_SOCKET_H

#include "linked_list.h"
#include <pthread.h>
#include "char_buffer.h"


GENERATE_LINKED_LIST(struct char_buffer, char_buffer);

/*
 * mozem urobit 1 vlakno v ktr volam socket start reading
 * v nom prebieha citanie kludne blokujuco
 *
 * v inom vlakne ich chcem spracovavat data
 * skus mi dat tie precitane data
 */


typedef struct active_socket {
    //pomocou neho komunikujem
    int socket_descriptor;
    const char* end_message;
    //nove -> ci citam data
    _Bool is_reading;
    pthread_mutex_t mutex_reading;
    pthread_mutex_t mutex_writing;

    //pamat cez zretazeny zoznam
    LINKED_LIST_char_buffer received_data;
    pthread_mutex_t mutex_received_data;
} ACTIVE_SOCKET;

void active_socket_init(struct active_socket* self);
void active_socket_destroy(struct active_socket* self);

//read je blokkujuca cakam kym mi nejake data nepridu
void active_socket_start_reading(struct active_socket* self);

// uz nechcem cakat
void active_socket_stop_reading(struct active_socket* self);
//otestovat ci som v stave
_Bool active_socket_is_reading(struct active_socket* self);
//pokusim sa ziskat neblokujuca operacia
// ak su data vrati mi ich v podobe charbuffra a true
//ak nie su len false
//vrati ich cele nie iba nejaku cast
_Bool active_socket_try_get_read_data(struct active_socket* self, struct char_buffer* output);

_Bool active_socket_is_end_message(struct active_socket* self, struct char_buffer* message);

void active_socket_write_data(struct active_socket* self, struct char_buffer* message);
void active_socket_write_end_message(struct active_socket* self);

#endif //SOCKETS_SERVER_ACTIVE_SOCKET_H
