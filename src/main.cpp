#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <string.h>

#include "qex.h"

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
    << "  FILE      input TSV (tab separated values) files.\n"
    << "  -h        Display help and exit.\n"
    << "  -r RANGE  Optional parameter specifying the date range from which\n"
    << "            queries are extracted.\n"
    << "  -n NUM    If present, extract the NUM most popular queries done\n"
    << "            within input files, optionally in the parametered date\n"
    << "            range."
    << std::endl;
}

/**
 * Parse input arguments, manage basic errors and returns a filled InputArgs
 * structure. It is the responsibility of the caller to print help and such,
 * this function automatically display usage and exit if necessary and exit
 * on error. */
static InputArgs parse_options (int argc, char** argv)
{
  InputArgs args;

  if (argc == 1)
  {
    /* print usage and early exit */
    usage();
    exit(1);
  }

  for (int i = 1; i < argc; ++i)
  {
    if (0 == strcmp("-h", argv[i]))
    {
      /* parse help option */
      args.help = true;
    }
    else if (0 == strcmp("-r", argv[i]))
    {
      /* parse range option with a required argument */
      ++i;
      if (i == argc)
      {
        std::cerr
          << "error: -r option requires an argument. Use qex -h for details\n";
        exit(1);
      }
      else
      {
        args.range = argv[i];
      }
    }
    else if (0 == strcmp("-n", argv[i]))
    {
      /* parse num option with a required argument */
      ++i;
      if (i == argc)
      {
        std::cerr
          << "error: -n option requires an argument. Use qex -h for details\n";
        exit(1);
      }
      else
      {
        try
        { args.num = std::stoi(argv[i]); }
        catch (std::exception&)
        {
          std::cerr
            << "error: integer expected as argument of -n option\n";
          exit(1);
        }
      }
    }
    else
    {
      /* assume to be an input file */
      {
        std::ifstream infile(argv[i]);
        if (!infile.good())
        {
          std::cerr
            << "error: unknown input file " << argv[i] << std::endl;
          exit(1);
        }
        args.files.push_back(argv[i]);
      }
    }
  }

  return args;
}

/************************* Entry point ***************************************/

int main(int argc, char** argv)
{
  /* parse arguments */
  InputArgs args = parse_options(argc, argv);

  if (args.help)
  {
    /* show help and exit */
    help();
    exit(1);
  }

  /* index input files */
  qex::Qex program;
  for (char* file : args.files)
  {
    std::string buffer;
    std::ifstream ifs{file};

    while (ifs.good())
    {
      std::getline(ifs, buffer);
      program.index_tsv_line(buffer.c_str());
    }
  }

  return 0;
}
