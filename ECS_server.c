#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024
int server_socket, client_socket, flag = 1;
int getupdateCo(int quantity_Carbon_monoxide) {
  printf("Adjusting the quantity of Carbon monoxide to minimum value\n");
  if (quantity_Carbon_monoxide < 1000) { // DECREMENTING CO VALUE

    while (quantity_Carbon_monoxide < 1000) {
      printf("%dppm of Carbon monoxide \n", 1000 - quantity_Carbon_monoxide);
      quantity_Carbon_monoxide += 10;
    }
  } else {
    // printf("Converting carbon Monoxide to carbon-di-oxide\n");

    while (quantity_Carbon_monoxide > 2000) {
      printf("%dppm of Carbon monoxide\n", quantity_Carbon_monoxide - 1000);
      quantity_Carbon_monoxide -= 10;
    }
  }
  return quantity_Carbon_monoxide;
}
int getupdateNOx(int Nitrogen_oxide) {
  printf("Adjusting the quantity of Nitrogen Oxide to minimum value\n");
  if (Nitrogen_oxide < 1000) {

    while (Nitrogen_oxide < 1000) {
      printf("%dppm of Nitrogen oxide \n", 1000 - Nitrogen_oxide);
      Nitrogen_oxide += 10;
    }
  } else {
    while (Nitrogen_oxide > 2000) {
      printf("%dppm of Nitrogen oxide \n", Nitrogen_oxide - 2000);
      Nitrogen_oxide -= 10;
    }
  }
  // strcpy(buf,"Your Engine is safe now");
  return Nitrogen_oxide;
}
int getupdateHC(int Hydro_Carbons) {
  printf("Adjusting the quantity of HydroCarbons to minimum value\n");
  if (Hydro_Carbons < 1000) {
    while (Hydro_Carbons < 1000) {
      printf("%dppm of HydroCarbons \n", 1000 - Hydro_Carbons);
      Hydro_Carbons += 10;
    }
  } else {
    while (Hydro_Carbons > 2000) {
      printf("%dppm of HydroCarbons \n", Hydro_Carbons - 2000);
      Hydro_Carbons -= 10;
    }
  }
  // strcpy(buf,"Your Engine is safe now");
  return Hydro_Carbons;
}

void handle_client(int client_socket) {
  char buffer[1024];
  char *fault;
  // Send first text data
  FILE *fd;
  fd = fopen("recordECSs.txt", "a");
  if (fd == NULL) {
    perror("FILE NOT EXIST\n");
    exit(0);
  }
  int quantity_Carbon_monoxide, Nitrogen_oxide, Hydro_Carbons;
  int flag = 0;

  printf("Enter the quantity of Carbon monoxide in ppm\n");
  scanf("%d", &quantity_Carbon_monoxide);
  printf("Enter the Quantity of Nitrogen oxide in ppm\n");
  scanf("%d", &Nitrogen_oxide);
  printf("Enter the Quantity of HydroCarbons in ppm \n");
  scanf("%d", &Hydro_Carbons);
  printf("\n");
  char text1[1024];
  while (flag == 0) {
    sprintf(text1, "%d", quantity_Carbon_monoxide);

    if (send(client_socket, text1, strlen(text1), 0) < 0) {
      perror("Cannot send to client\n");
    }
    memset(buffer, '\0', sizeof(buffer));
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0) {
      perror("Cannot receive from client\n");
    }
    printf("Received Acknoledgement FROM CLIENT :%s\n", buffer);
    fprintf(fd, "Received Acknoledgement FROM CLIENT :%s\n", buffer);

    fault = strtok(buffer, ":");
    if (strcmp(fault, "OK") == 0) {
      printf("QUANTITY OF Carbon monoxide IS MINIMUM\n");
      fprintf(fd, "QUANTITY OF Carbon monoxide IS MINIMUM\n");
      flag = 1;
    } else {
      fprintf(fd,
              "Adjusting the quantity of Carbon monoxide to minimum value\n");
      quantity_Carbon_monoxide = getupdateCo(quantity_Carbon_monoxide);
    }
  }
  // send(client_socket, text1, strlen(text1), 0);
  printf("Sent Carbon monoxide to client.\n");
  fprintf(fd, "Sent Carbon monoxide to client.\n\n");
  printf("\n");

  // Send second text data
  sleep(1); // Introducing a delay for demonstration purposes
  char text2[1024];
  flag = 0;
  while (flag == 0) {
    sprintf(text2, "%d", Nitrogen_oxide);

    if (send(client_socket, text2, strlen(text2), 0) < 0) {
      perror("Cannot send to client\n");
    }

    memset(buffer, '\0', sizeof(buffer));
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0) {
      perror("cannot receive from client\n");
    }
    printf("Received Acknoledgement FROM CLIENT  :%s\n", buffer);
    fprintf(fd, "Received Acknoledgement FROM CLIENT  :%s\n", buffer);

    fault = strtok(buffer, ":");
    if (strcmp(fault, "OK") == 0) {
      printf("QUANTITY OF Nitrogen oxide IS MINIMUM\n");
      fprintf(fd, "QUANTITY OF Nitrogen oxide IS MINIMUM\n");
      flag = 1;
    } else {
      fprintf(fd,
              "Adjusting the quantity of Nitrogen Oxide to minimum value\n");
      Nitrogen_oxide = getupdateNOx(Nitrogen_oxide);
    }
  }
  printf("Sent NITROGEN OXIDE to client.\n");
  fprintf(fd, "Sent NITROGEN OXIDE to client.\n\n");
  printf("\n");

  // Send third text data
  sleep(1); // Introducing a delay for demonstration purposes
  char text3[1024];
  flag = 0;
  while (flag == 0) {
    sprintf(text3, "%d", Hydro_Carbons);
    if (send(client_socket, text3, strlen(text3), 0) < 0) {
      perror("Cannot send to client\n");
    }
    memset(buffer, '\0', sizeof(buffer));
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0) {
      perror("Cannot receive from client\n");
      exit(0);
    }
    printf("Received Acknoledgement from client:%s\n", buffer);
    fprintf(fd, "Received Acknoledgement from client:%s\n", buffer);

    fault = strtok(buffer, ":");
    if (strcmp(buffer, "OK") == 0) {
      printf("QUANTITY OF HYDROCARBONS IS MINIMUM\n");
      fprintf(fd, "\nQUANTITY OF HYDROCARBONS IS MINIMUM\n");
      flag = 1;
    } else {
      fprintf(fd,
              "\nAdjusting the quantity of HydroCarbons to minimum value\n");
      Hydro_Carbons = getupdateHC(Hydro_Carbons);
    }
  }
  printf("Sent HYDROCARBONS DATA to client.\n");
  fprintf(fd, "Sent HYDROCARBONS DATA to client.\n\n");
  fclose(fd);
}

int main() {
  FILE *fd;
  fd = fopen("recordECSs.txt", "a");
  if (fd == NULL) {
    perror("FILE NOT EXIST\n");
    exit(0);
  }
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len = sizeof(client_addr);

  // Create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // Set up server address struct
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT); // host to network byte

  // Bind the socket socket_file_discripter ,(struct socaddr) typecasted
  // server_addr and address length
  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == -1) {
    perror("Error binding");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections Socket_fd and max len of q
  if (listen(server_socket, 5) == -1) {
    perror("Error listening");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);
  fprintf(fd, "Server listening on port %d...\n", PORT);
  fclose(fd);

  while (1) {
    // Accept connection from client sock_fd struct sockaddr type addr len
    client_socket =
        accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket == -1) {
      perror("Error accepting connection");
      close(server_socket);
      exit(EXIT_FAILURE);
    }
    // inet_ntoa convert host network bytes to string
    // ntohs() convert network byte order to host byte order
    printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    // Handle the client
    handle_client(client_socket);
    // close(server_socket);
    return 0;
  }
  if (close(server_socket) == -1) {
    exit(1);
  }
  return 0;
}
