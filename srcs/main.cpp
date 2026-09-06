#include "config.hpp"

int	main()
{
	Logger& logger = Logger::getInstance();

	logger.enableConsoleOutput(true);
	logger.setLogLevel(Logger::LogLevel::WARNING);
	logger.info("Cloud-System started");

	try
	{
		GE::Window window(100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, "Cloud System", 4.6f, &logger);

		initRendering(window, logger);
	}
	catch(const exception& e)
	{
		logger.fatal(string("Catched fatal error: ") + e.what());
	}

	
	logger.info("Cloud-System stopped");

	return 0;
}