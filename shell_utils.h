#ifndef SHELL_UTILS
#define SHELL_UTILS

#include <gtk-4.0/gtk/gtk.h>

typedef struct _CallBackData { 
    GtkEntry *IP;
    char *ReturnVal;
} CallBackData;

CallBackData *init_callback_data(GtkEntry *entry);
void nmap(CallBackData data);

#endif // !SHELL_UTILS