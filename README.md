# qex

Queries extractor tool. Built for the Algolia tech test. The goal of this test
is here:
https://gist.github.com/Nagriar/69d00251b8e945dcad17a8de17d38869

## Build Guide

qex is built using CMake. It requires 'cmake' and a C++ compiler to be
installed on the host computer.

To build qex, follow these steps:

```bash
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

The `qex` binary is expected to be produced in `<ROOT>/build/qex`.

## Synopsis

```
qex [-h] [-r RANGE] [-n NUM] FILE [FILE ...]
```

## Overview

qex is a command line tool which takes as input TSV files containing any number
of lines that follow this format
`<YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>\t<QUERY>\n` and options which
parameters the outputs to extract from the input queries files.

Depending on the input options, qex is able to output The number of distinct
queries done during a specific time range. Follows some example use-cases.

Number of distinct queries done in 2017:

```bash
$ qex -r 2017 data.tsv
178930
```
Queries done the 20th day of every months of 2016 the 20th minute of every hour:

```bash
$ qex -r "2016-*-20 *:20" data.tsv
8976
```

All queries:

```bash
$ qex data.tsv
4982938
```

qex is also able to output the top N most popular queries done during a specific
time range, one per line sorted in descending order. Follows some example
use-cases.

Top 3 queries:

```bash
$ qex -n 3 data.tsv
golang 28727
http://google.com 8927
toto 2019
```

Top query done the 1st march of 2017:

```bash
$ qex -n 1 data.tsv -r "2017-03"
Manu%20au%20salon%20de%20l%20argriculture 1092837
```

If no input is given the qex, it prints its usage and exit.

```bash
$ qex
Usage: qex [-h] [-r RANGE] [-n NUM] FILE [FILE ...]
```

## Complexity

Let **n** be the number of queries in the input file(s) and **m** be the
number of indexed queries, which are queries in the input date range.
Here is the space and time complexity of qex:

* Space: O(n + 2m)
* Time: O(n + 2m*log(m))