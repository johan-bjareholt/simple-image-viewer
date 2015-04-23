//#include <config.h>
#include <gtk/gtk.h>

const char* programname = "simple image viewer";
const char* shortprogramname = "siv";
char* filename;

static void open_image(gchar* filename, gpointer user_data){
    GtkWidget* image = GTK_WIDGET(user_data);
    gtk_image_set_from_file (GTK_IMAGE(image), filename);
}

static void on_open_image (GtkButton* button, gpointer user_data)
{
    open_image(filename, user_data);
}

static void on_open_image_keypress (GtkButton* button, GdkEvent* event, gpointer user_data)
{
    open_image(filename, user_data);
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
    open_image(filename, image);

	gtk_box_pack_start (GTK_BOX (box), image, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (window), box);

    //g_signal_connect (window, "key-release-event", G_CALLBACK(on_open_image_keypress), image);

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

    filename = argv[1];
    //printf("%s\n", filename);
    gtk_init (&argc, &argv);
    create_window();
    gtk_main();

    return;
}
