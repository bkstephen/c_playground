#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include "shell_utils.h"

static void on_activate(GtkApplication *app) {
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
    
    // Create grid to attach the stuff
    GtkWidget *grid   = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid),5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);

    // Input field
    GtkWidget *ip_field = gtk_entry_new();
    CallBackData *data = init_callback_data(ip_field);

    // Buttons
    GtkWidget *nmap_button = gtk_button_new_with_label("nmap");
    GtkWidget *get_input_button = gtk_button_new_with_label("Get input");

    // Attack items on main UI
    gtk_grid_attach(GTK_GRID(grid), nmap_button, 0, 1, 5, 1);
    gtk_grid_attach(GTK_GRID(grid), get_input_button, 0, 2, 5, 1);
    gtk_grid_attach(GTK_GRID(grid), ip_field, 0, 4, 5, 1);

    // When the button is clicked, close the window passed as an argument
    //g_signal_connect_swapped(nmap_button, "clicked", G_CALLBACK(gtk_window_close), window);
    g_signal_connect_swapped(nmap_button, "clicked", G_CALLBACK(nmap), data);
    //g_signal_connect_swapped(get_input_button, "clicked", G_CALLBACK(print_entry), ip_field);
    
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    // Create a new application
    GtkApplication *app = gtk_application_new("com.pentestapp.GtkApplication", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);    
    return g_application_run(G_APPLICATION(app), argc, argv);
}
