#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-4.0/gtk/gtk.h>
#include "shell_utils.h"

char * NMAP_CMD = "-c /usr/bin/nmap -sC -sV -T4 -A ";

CallBackData *init_callback_data(GtkWidget **entry) {
    CallBackData * data = malloc(sizeof(CallBackData));
    data->IP = *entry;
    return data;
}

static char *get_entry_field_ip(GtkWidget *entry_field) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry_field);
    const char *text = gtk_entry_buffer_get_text(buffer);    
    return text;
}

static char *run_command(char *cmd)
{
  FILE *fp;
  char _res[BUFSIZ];
  char *output = (char*)malloc(BUFSIZ);

  const char * shell_path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
  fp = execl(shell_path, "/bin/bash", "-c", cmd, (char *)0);

  //fp = popen(cmd, "r");

  if (fp == NULL) {
    g_print("Failed to run command\n" );
    return NULL;
  }

  while (fgets(_res, sizeof(_res), fp) != NULL) {
    size_t new_len = sizeof(_res) + sizeof(output);
    output = realloc(output, new_len);
    strcat(output, _res);    
  }

  pclose(fp);
  return output;
}

void nmap(CallBackData *data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(data->IP);
    const char *ip = gtk_entry_buffer_get_text(buffer);

    char *cmd[sizeof(NMAP_CMD) + sizeof(*ip)];
    strcat(cmd, NMAP_CMD);
    strcat(cmd, ip);

    data->ReturnVal = run_command(cmd);

    g_print("%s\n",cmd);
    g_print("%s\n",data->ReturnVal);
}
