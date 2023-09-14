#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <vector.h>


#include "../src/debug.h"
#include "../src/parser.h"
 

static const char * progname     = "ecc";
static const char * prog_version = "0.2.0";
static const char * compile_date = __DATE__; 


static bool dump_ast;
static char * output;
static bool makefile_dep;
static int warning_level;
static FILE * debug_stream;
static int optim_level;
static bool compile_only;
static bool assembly_only;
static Vector(char *) * lib_path;
static Vector(char *) * include_path;
static Vector(char *) * lib;
static Vector(char *) * input;


void
version(FILE * stream)
{
    fprintf(
        stream
        , "%s version %s compiled on %s\n"
        , progname
        , prog_version
        , compile_date);
}


void
help(FILE * stream)
{
    fprintf(
        stream
        , "Ussage: %s [options...] [--] <filename>\n"
          "        %s --version\n"
        , progname
        , progname);

    fputs(
          "\n"
          "System options\n"
          "    -h            show this text and exit (also --help)\n"
          "    --version     prints compiler version info and exit\n"
          "\n"
          "General options\n"
          "    -fdump-ast    print AST\n"
          "    -o <outfile>  write output to outfile\n"
          "    -M            generate Makefile dependencies on stdout\n"
          "\n"
          "Info messages output options\n"
          "    -Wall         enable all warning messages\n"
          "    -Z<file>      redirect debug messages to file\n"
          "\n"
          "Optimizations options\n"
          "    -Oflags...    optimize opcodes, immediates and branch offsets\n"
          "       -O0        no optimization\n"
          "       -O1        minimal optimization\n"
          "       -Ox        multipass optimization (default)\n"
          "\n"
          "Compilation process options\n"
          "    -I<path>      add the include path\n"
          "    -c            compile or assemble the source files, but do not link.\n"
          "    -s            generate assembler output\n"
          "\n"
          "Lingking process options\n"
          "    -l<library>   Search the library named library when linking\n"
          "    -L<dir>       Add directory dir to the list of directories to be searched for -l\n"
        , stream);
}


static void
parse_cmd_opt(
    int argc
    , char **argv)
{
    const struct option long_options[] =
    {
        {"version", no_argument, NULL, 0}
        , {"help",   no_argument,  NULL, 'h'}
        , {0, 0, 0, 0}
    };

    const char * short_options = "W:I:L:l:f:hscMo:O:Z:";

	if(argc == 1)
    {
		fprintf(stderr, "%s: ", progname);
		FATAL(
            stderr
            , "no input files\n"
		      "compilation terminated.");
        exit(EXIT_FAILURE);
    }

	int opt_id;
    
	while((opt_id = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch(opt_id)
        {
		case 0: 
			version(stdout);
			exit(0);
		case 'f':
			dump_ast = true;
			break;
		case 'O':
			optim_level = 0;
			printf("-O option is not implemented yet.\n");
			break;
		case 'W':
			if(strcmp(optarg, "all") == 0)
				warning_level = 1;
			else if(strcmp(optarg, "extra") == 0)
				warning_level = 2;
			else
			{
				fprintf(stderr, "%s: ", progname);
				ERROR(stderr, "Unknown warning level '%s'\n", optarg);
			}
		   	break; 
		case 'I':
			if(include_path == NULL)
				include_path = vector_new(sizeof(char*), 1);
			else
				include_path = vector_resize(VECTOR(include_path), VECTOR(include_path)->length+1);
			
			include_path[VECTOR(include_path)->length-1] = optarg;		
		   	break;
		case 'L':
			if(lib_path == NULL)
				lib_path = vector_new(sizeof(char*), 1);
			else
				lib_path = vector_resize(VECTOR(lib_path), VECTOR(lib_path)->length+1);
			
			lib_path[VECTOR(lib_path)->length-1] = optarg;		
		   	break;
		case 'l':
			if(lib == NULL)
				lib = vector_new(sizeof(char*), 1);
			else
				lib = vector_resize(VECTOR(lib), VECTOR(lib)->length+1);
			
			lib[VECTOR(lib)->length-1] = optarg;		
			break;
		case 'h':
			help(stdout);
			exit(0);
		case 'c':
			compile_only = true;
			printf("-c option is not implemented yet.\n");
			break;
		case 's':
			assembly_only = true;
			printf("-s option is not implemented yet.\n");
			break;
		case 'M':
			makefile_dep = false;
			printf("-M option is not implemented yet.\n");
			break;
		case 'o':
			output = optarg;
			break;
		case 'Z':
			FILE* stream = fopen(optarg, "w");
			
			if(stream == NULL)
			{	
				fprintf(stderr, "%s: ", progname);
				FATAL(stderr, "open file for debug output: '%s'\n", optarg);
				exit(EXIT_FAILURE);
			}
			
			debug_stream = stream;
			break;
		case '?':
			fprintf(stderr, "%s: ", progname);
			FATAL(stderr, "unrecognized command-line option '%s'\n", optarg);
			exit(EXIT_FAILURE);
			break;
		default:
			fprintf(stderr, "%s: ", progname);
			FATAL(stderr, "unrecognized command-line option '%s'\n", optarg);
			exit(EXIT_FAILURE);
        }
    }

    for (int i = optind; i < argc; i++)
	{
      	if(input == NULL)
			input = vector_new(sizeof(char*) , 1);
		else
			input = vector_resize(VECTOR(input), VECTOR(input)->length+1);
		
		input[VECTOR(input)->length -1] = argv[i];
    }
}


int
main(int argc, char ** argv)
{
	/************************* initialization ***************************/
	debug_stream = stdout;
	parse_cmd_opt(argc, argv);



	/***************************** cleanup *******************************/
	if(lib != NULL)
		vector_delete(VECTOR(lib));

	if(include_path != NULL)
		vector_delete(VECTOR(include_path));

	if(lib_path != NULL)
		vector_delete(VECTOR(lib_path));

	if(input != NULL)
		vector_delete(VECTOR(input));

	if(debug_stream != NULL)
		fclose(debug_stream);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



