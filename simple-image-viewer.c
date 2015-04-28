//#include <config.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "filenamenode.h"

const char* programname = "simple image viewer";
const char* shortprogramname = "siv";

struct FilenameNode* selectedPicture;

static void open_image(const char* filename, gpointer user_data){
    GtkWidget* image = GTK_WIDGET(user_data);
    gtk_image_set_from_file (GTK_IMAGE(image), filename);
    printf("Opening %s\n", filename);
}

static void open_next_image(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    selectedPicture = selectedPicture->next;
    open_image(selectedPicture->filename, user_data);
}


static void create_window ()
{
	GtkWidget *window;
	GtkWidget *image;
	GtkWidget *box;

	// Set up the UI
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), programname);
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

	image = gtk_image_new ();
    open_image(selectedPicture->filename, image);

	gtk_box_pack_start (GTK_BOX (box), image, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (window), box);

    // Open next image when any key is pressed
    g_signal_connect (window, "key-release-event", G_CALLBACK(open_next_image), image);

	// Exit when the window is closed
	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}

void main (int argc, char **argv)
{
    if (argc < 2){
        printf("Please specify a image to display\n");
        return;
    }

    struct FilenameNode* firstPicture = newFilenameNode(argv[1], NULL, NULL);
    firstPicture->next = firstPicture;
    firstPicture->prev = firstPicture;

    struct FilenameNode* previousPicture = firstPicture;
    for (int i=2; i<argc; i++){
        struct FilenameNode* picture = newFilenameNode(argv[i], firstPicture, previousPicture);
        firstPicture->prev = picture;
        previousPicture->next = picture;
        previousPicture = picture;

        printf("%s <- %s -> %s\n", previousPicture->prev->filename, previousPicture->filename, previousPicture->next->filename);
    }
    printf("%s <- %s -> %s\n", firstPicture->prev->filename, firstPicture->filename, firstPicture->next->filename);

    selectedPicture = firstPicture;

    //printf("%s\n", filename);
    gtk_init (&argc, &argv);
    create_window();
    gtk_main();

    //deleteFilenameNode(selectedPicture);
    deleteAllFilenameNodes(selectedPicture);

    return;
}
