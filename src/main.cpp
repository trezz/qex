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

  /* create range object from input argument if present */
  qex::Range* range = nullptr;
  if (args.range != nullptr)
  { range = new qex::Range(args.range); }

  /* index input files */
  qex::Qex program(args.range);
  std::unordered_map<std::string, char*> buffers;

  for (char* file : args.files)
  {
    /* read whole file content into buffer */
    std::ifstream ifs;
    size_t length;
    ifs.open(file);
    ifs.seekg(0, std::ios::end);
    length = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    buffers[file] = new char[length];
    ifs.read(buffers[file], length);
    ifs.close();

    /* index the file using Qex object and catch eventual errors */
    try
    {
      size_t lineno = 1;
      for (char* line = buffers[file];
           line;
           line = program.index_tsv_line(line, lineno))
      { ++lineno; }
    }
    catch (std::string& msg)
    {
      std::cerr << "error: " << msg << std::endl;
    }
    catch (std::exception& e)
    {
      std::cerr << "error: " << e.what() << std::endl;
    }
  }

  /* extract queries based on input arguments */
  if (args.num == 0)
  {
    std::cout << program.num_distinct_queries() << std::endl;
  }
  else
  {
    program.build_most_popular_queries_set();
    program.print_nth_most_popular_queries(args.num);
  }

  for (auto& file_buffer : buffers)
  { delete file_buffer.second; }

  if (range)
  { delete range; }

  return 0;
}
