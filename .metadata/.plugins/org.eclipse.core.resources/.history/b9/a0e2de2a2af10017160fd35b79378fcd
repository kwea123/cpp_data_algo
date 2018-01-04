#include <boost/python.hpp>
#include <pygtk/pygtk.h>
#include <gtkmm.h>

using namespace boost::python;
using namespace std;

// This is called in the idle loop.
bool update(object *axes, object *canvas) {
    static object random_integers = object(handle<>(PyImport_ImportModule("numpy.random"))).attr("random_integers");
    axes->attr("scatter")(random_integers(0,1000,1000), random_integers(0,1000,1000));
    axes->attr("set_xlim")(0,1000);
    axes->attr("set_ylim")(0,1000);
    canvas->attr("draw")();
    return true;
}

int main() {
    try {
        // Python startup code
        Py_Initialize();
        PyRun_SimpleString("import signal");
        PyRun_SimpleString("signal.signal(signal.SIGINT, signal.SIG_DFL)");

        // Normal Gtk startup code
        Gtk::Main kit(0,0);

        // Get the python Figure and FigureCanvas types.
        object Figure = object(handle<>(PyImport_ImportModule("matplotlib.figure"))).attr("Figure");
        object FigureCanvas = object(handle<>(PyImport_ImportModule("matplotlib.backends.backend_gtkagg"))).attr("FigureCanvasGTKAgg");

        // Instantiate a canvas
        object figure = Figure();
        object canvas = FigureCanvas(figure);
        object axes = figure.attr("add_subplot")(111);
        axes.attr("hold")(false);

        // Create our window.
        Gtk::Window window;
        window.set_title("Engineering Sample");
        window.set_default_size(1000, 600);

        // Grab the Gtk::DrawingArea from the canvas.
        Gtk::DrawingArea *plot = Glib::wrap(GTK_DRAWING_AREA(pygobject_get(canvas.ptr())));

        // Add the plot to the window.
        window.add(*plot);
        window.show_all();

        // On the idle loop, we'll call update(axes, canvas).
        Glib::signal_idle().connect(sigc::bind(&update, &axes, &canvas));

        // And start the Gtk event loop.
        Gtk::Main::run(window);

    } catch( error_already_set ) {
        PyErr_Print();
    }
}
