#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-4.0/gtk/gtk.h>
#include "shell_utils.h"

CallBackData *init_callback_data(GtkEntry *entry) {
    CallBackData data;
    data.IP = entry;
    return &data;
}

static char *get_entry_field_ip(GtkEntry *entry_field) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry_field);
    const char *text = gtk_entry_buffer_get_text(buffer);    
    return text;
}

static char *run_command(char *cmd)
{
  FILE *fp;
  char _res[BUFSIZ];
  char *output = (char*)malloc(BUFSIZ);

  fp = popen(cmd, "r");

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

void nmap(CallBackData data) {
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(data.IP);
    const char *text = gtk_entry_buffer_get_text(buffer);    
    data.ReturnVal = run_command("ls");
    g_print(text);
    g_print(data.ReturnVal);
}
