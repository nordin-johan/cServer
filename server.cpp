#include "./lib/mongoose.c"
#include <string>

// Struct containing settings for how to serve HTTP
static struct mg_serve_http_opts s_http_server_opts;

class Server {

	private:

		/**
		 * ev_handler
		 */
		static void ev_handler(struct mg_connection *nc, int ev, void *p) {

			// If event is http request, serve static html files
			if (ev == MG_EV_HTTP_REQUEST)
				mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);

		}

	public: 

		/**
		 * init
		 */
		int init(int port) {

			// Mongoose event manager
			struct mg_mgr mgr;

			// Mongoose connection
			struct mg_connection *nc;

			// Convert port to char
			std::string portToChar = std::to_string(port);
			static char const *sPort = portToChar.c_str();

			// Init mongoose
			mg_mgr_init(&mgr, NULL);
			std::cout << "Starting web server on port " << sPort << std::endl;

			nc = mg_bind(&mgr, sPort, ev_handler);

			// If connection fails
			if (nc == NULL) {
				std::cout << "Failed to create listener" << std::endl;
				return 1;
			}

			// Set up HTTP server options
			mg_set_protocol_http_websocket(nc);
			s_http_server_opts.document_root = ".";
			s_http_server_opts.enable_directory_listing = "yes";

			for (;;)
				mg_mgr_poll(&mgr, 1000);

			// Free up all memory allocated
			mg_mgr_free(&mgr);

			return 0;
		 
		}

};