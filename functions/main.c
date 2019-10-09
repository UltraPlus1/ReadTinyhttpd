/***********************************************************************************/
/*主函数：
 *
 * 
 * /
/***********************************************************************************/ 
int main(void)
{
  int server_sock = -1; //创建服务器端socket 
  u_short port = 0;     //服务器端socket端口号
  int client_sock = -1; //客户端socket 
  struct sockaddr_in client_name;//ipv4结构体[1]
  socklen_t client_name_len = sizeof(client_name);//地址的长度
  pthread_t newthread;//线程的标识符

  server_sock = startup(&port);
  printf("httpd running on port %d\n", port);

  while (1)
  {
    client_sock = accept(server_sock,
                         (struct sockaddr *)&client_name,
                         &client_name_len);
    if (client_sock == -1)
      error_die("accept");
    //accept_request(client_sock);
    if (pthread_create(&newthread, NULL, accept_request, (void *)&client_sock) != 0)
      perror("pthread_create");
  }

  close(server_sock);

  return (0);
}
/*************************************************************************************/
/*[1]: 
   struct sockaddr_in {
    sa_family_t    sin_family; //typedef    u_short    sa_family_t;
    in_port_t      sin_port;   //typedef	__uint16_t		in_port_t;
    struct in_addr sin_addr;   
    };
   typedef unsigned long int pthread_t 


