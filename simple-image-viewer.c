//#include <config.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdbool.h>

#include "filenamenode.h"

const char* programname = "simple image viewer";
const char* shortprogramname = "siv";

struct FilenameNode* selectedPicture;

GtkWindow* window;

static bool open_image(struct FilenameNode* filenamenode, gpointer user_data){
    GtkImage* image = GTK_IMAGE(user_data);
    gtk_image_set_from_file (image, filenamenode->filename);

    const GdkPixbuf *pb = gtk_image_get_pixbuf(image);
    if (pb != NULL){
        gtk_window_resize(window, gdk_pixbuf_get_width(pb), gdk_pixbuf_get_height(pb));
        printf("Opened %s\n", filenamenode->filename);
        return true;
    }
    else {
        printf("Couldn't open %s\n", filenamenode->filename);
        deleteFilenameNode(filenamenode);
        return false;
    }
}

static void open_next_image(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    switch (event->keyval){
        case GDK_KEY_d:
        case GDK_KEY_j:
        case GDK_KEY_Right:
            selectedPicture = selectedPicture->next;
            while( !open_image(selectedPicture, user_data))
                selectedPicture = selectedPicture->next;
            break;
        case GDK_KEY_a:
        case GDK_KEY_k:
        case GDK_KEY_Left:
            selectedPicture = selectedPicture->prev;
            while( !open_image(selectedPicture, user_data) )
                selectedPicture = selectedPicture->prev;
            break;
        default:
            break;
    }
}


static void create_window ()
{
	GtkWidget* box;
    GtkImage* image;

	// Set up the UI
	window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), programname);
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

    image = (GtkImage*)gtk_image_new();
    open_image(selectedPicture, image);

	gtk_box_pack_start (GTK_BOX (box), (GtkWidget*)image, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (window), box);

    // Open next/prev image when left/right/a/d/j/k is pressed
    g_signal_connect (window, "key-release-event", G_CALLBACK(open_next_image), image);

	// Exit when the window is closed
	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all((GtkWidget*)window);
}

void main (int argc, char **argv)
{
    if (argc < 2){
        printf("Please specify a image to display\n");
        return;
    }
    // Initialize
    loadFilenames(argc, argv);
    gtk_init (&argc, &argv);
    create_window();
    // Run
    gtk_main();
    // Cleanup
    deleteAllFilenameNodes(selectedPicture);

    return;
}
