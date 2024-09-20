#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-4.0/gtk/gtk.h>
#include "shell_utils.h"

char * OUTPUT_FILE = "scan_results.txt";
char * NMAP_CMD = ";nmap -sC -sV -T4 -A ";

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
  char output[256];
  //char *output = malloc(sizeof(char));

  fp = popen(cmd, "r");

  if (fp == NULL) {
    strcpy(output, "Command failed to run: ");
    strcat(output, cmd);
    return output;
  }

  // Wait the results
  while (fgets(_res, sizeof(_res), fp) != NULL){}
    // size_t new_len = sizeof(_res) + sizeof(output);
    // output = realloc(output, new_len);
    // strcat(output, _res);    
  //}

  pclose(fp);

  strcpy(output, "Command ran successfully, check for results in ");
  strcat(output, OUTPUT_FILE);
  return output;
}

void nmap(CallBackData *data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(data->IP);
    const char *ip = gtk_entry_buffer_get_text(buffer);

    char *cmd[sizeof(NMAP_CMD) + sizeof(*ip) + sizeof(OUTPUT_FILE) + 2];
    strcat(cmd, NMAP_CMD);
    strcat(cmd, ip);
    strcat(cmd, ">");
    strcat(cmd, OUTPUT_FILE);

    data->ReturnVal = run_command(cmd);

    //g_print("%s\n",cmd);
    g_print("%s\n",data->ReturnVal);
}
