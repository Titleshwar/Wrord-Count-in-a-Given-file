#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <string>

GtkWidget *entry;
GtkWidget *label;

static void countWords(GtkWidget *widget, gpointer data) {
    const gchar *filename = gtk_entry_get_text(GTK_ENTRY(entry));

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        gtk_label_set_text(GTK_LABEL(label), "Error: Unable to open file.");
        return;
    }

    std::string word;
    int wordCount = 0;
    while (inputFile >> word) {
        wordCount++;
    }
    inputFile.close();

    std::string result = "Total words: " + std::to_string(wordCount);
    gtk_label_set_text(GTK_LABEL(label), result.c_str());
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Word Count");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Create layout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create entry
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);

    // Create button
    GtkWidget *button = gtk_button_new_with_label("Count Words");
    g_signal_connect(button, "clicked", G_CALLBACK(countWords), nullptr);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    // Create label
    label = gtk_label_new("Enter the file name and press 'Count Words'.");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the main loop
    gtk_main();

    return 0;
}

