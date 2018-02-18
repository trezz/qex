#include <iostream>
#include <vector>

/** Holds the inputs arguments. */
struct InputArgs
{
  /**
   * Default inputs with input files will show the total number of queries
   * in the input file(s). If no file is given, then the program usage should be
   * displayed. */
  InputArgs ()
    : help(false), range(nullptr), num(0), files()
  { }

  bool help;
    /**< Option -h given. Show help and exit. */
  char* range;
    /**< Date range. Pointer to the input argument or NULL if no range. */
  int num;
    /**< Number of results to display. Value 0 behave as if -q were given and
     * the total number of queries is displayed. */
  std::vector<char*> files;
    /**< Input file paths. */
};

/** Print usage */
static void usage ()
{
  std::cout << "Usage: qex [-h] [-r RANGE] [-n NUM] FILE [FILE ...]"
            << std::endl;
}

/** Print help */
static void help ()
{
  usage();
  std::cout
    << std::endl
    << "qex is a command line tool which takes as input TSV files containing\n"
    << "any number of lines that follow this format\n"
    << "`<YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>\\t<QUERY>\\n` and options\n"
    << "which parameters the outputs to extract from the input queries files.\n"
    << "Depending on the input options, qex is able to output The number of\n"
    << "distinct queries done during a specific time range. Follows some\n"
    << "example use-cases.\n"
    << std::endl
    << "Options:\n"
    << std::endl
}

/************************* Entry point ***************************************/

int main(int argc, char** argv)
{
  std::cout << "Hello world!" << std::endl;
  return 0;
}