#include <iostream>
#include <cmath>
#include <chrono>
#include <time.h>
#include <thread>
#include "mainpqthread.h"

//Date of creation: 02.08.2022
//Author: ZombiDebugWall
//Windows edition

void _list_help_func()
{
	std::cout << "PQBench (testphase) by ZombiDebugWall" << std::endl;
	std::cout << "Usage: pqbench [parameter]" << std::endl;
	std::cout << "-t, 	--time\t\t\t\tMeasures time and calculations per ms [DEFAULT]\n" << std::endl;
	std::cout << "-cs, 	--check-status\t\t\tShows if test is running properly or freezing" << std::endl;
	std::cout << "\t\t\t\t\tNOTE: This parameter might reduce performance (Use -t for proper performance testing)\n" << std::endl;
	std::cout << "-oc,	--overclocking\t\t\tThis parameter measures calculations per second in realtime, made for realtime overclocking" << std::endl;
	std::cout << "\t\t\t\t\tNOTE: This parameter will reduce performance due to realtime measurements (Again, use -t for proper performance testing)\n" << std::endl;
	std::cout << "-h	--help\t\t\t\tprint this message" << std::endl;

}


void progress_of_run()
{
	std::chrono::milliseconds sleepfor(1000);
	std::this_thread::sleep_for(sleepfor);

	char loading_icon[4] = {'|', '/', '-', '\\'};
	int loading_index = 0;

	while (!PQGlobVar::finished)
	{	
		fprintf(stderr,"\033[2J");
		fprintf(stderr,"\033[H");
		fprintf(stderr, "Benchmark is running...%c\n", loading_icon[loading_index]);

		if (loading_index == 3)
		{
			loading_index = 0;
		}
		else
		{
			loading_index++;
		}

		std::this_thread::sleep_for(sleepfor);
	}


}






void calcpq_bench()
{
	long double p = 1276.5635;
	long double q = 867.3649;
	long double amount_of_runs= 50000000000;
	long double i = 0;
	
	long double quotient;
	long double sqroot_of;
	long double zero_point_left;
	long double zero_point_right;

	std::cout << "Benchmark is running..." << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();

	for (; i < amount_of_runs; i += 1)
	{
		quotient = -(p / 2);
		
		sqroot_of = sqrt((((p / 2) * (p / 2)) - q));
		zero_point_left = quotient - sqroot_of;
		zero_point_right = quotient + sqroot_of;
		
		//std::chrono::milliseconds sleepfor(1000);
		//std::this_thread::sleep_for(sleepfor);	

		p += 1276.4343757;
		q += 867.653543376;
	}
	


	/*auto end = std::chrono::high_resolution_clock::now();
	finished = true;
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(end-begin).count() << "s" << std::endl;*/ //Old


	auto end = std::chrono::high_resolution_clock::now();
	
	
	PQGlobVar::finished = true;
	
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;
	std::cout << double(amount_of_runs / std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) << " calculations per millisecond" << std::endl;
	std::cout << "Last point left: " << zero_point_left << std::endl;
	std::cout << "Last point right: " << zero_point_right << std::endl;
	//fprintf(stderr, "%f", double(amount_of_runs / std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()));


}





void calcpq_bench_realtime_overclocking()
{
	long double p = 1276.5635;
	long double q = 867.3649;
	
	
	long double i = 0;
	long double amount_of_runs= 950000000000;
	
	PQGlobVar::iptr = &i;
	PQGlobVar::amount_of_runsptr = &amount_of_runs;

	long double quotient;
	long double sqroot_of;
	long double zero_point_left;
	long double zero_point_right;


	long double current_speed_begin = 0;
	long double current_speed_stop = 0;
	long double current_speed = 0;

	auto measure_begin = std::chrono::high_resolution_clock::now();
	auto measure_end = std::chrono::high_resolution_clock::now();



	while(true)
	{
		
		for (; i < amount_of_runs; i += 1)
		{
			quotient = -(p / 2);
			
			sqroot_of = sqrt((((p / 2) * (p / 2)) - q));
			zero_point_left = quotient - sqroot_of;
			zero_point_right = quotient + sqroot_of;
			
			//std::chrono::milliseconds sleepfor(1000);
			//std::this_thread::sleep_for(sleepfor);	

			p += 1276.4343757;
			q += 867.653543376;

			measure_end= std::chrono::high_resolution_clock::now();

			if (std::chrono::duration_cast<std::chrono::milliseconds>(measure_end-measure_begin).count() > 1000)
			{
				current_speed_stop = *PQGlobVar::iptr;
				current_speed = current_speed_stop - current_speed_begin;
				fprintf(stderr,"\033[2J");
				fprintf(stderr,"\033[H");
				fprintf(stderr, "Current calculations per second: %.0Lf \n", current_speed);
				fprintf(stderr, "Current value (left): %.10Lf \n", zero_point_left);
				fprintf(stderr, "Current value (right): %.10Lf \n", zero_point_right);
				measure_begin = std::chrono::high_resolution_clock::now();
				current_speed_begin = *PQGlobVar::iptr;
			}
		}
	
		
		i = 0;
		p = 1276.5635;
		q = 867.3649;
		measure_begin = std::chrono::high_resolution_clock::now();
		measure_end = std::chrono::high_resolution_clock::now();

	}
}





int main(int argc, char *argv[])
{
	//std::thread thread_progress(progress_of_run);
	//std::thread thread_bench(calcpq_bench);
	//thread_progress.join();
	//thread_bench.join();

	std::string argument = " ";

	if (argc == 2)
	{
		argument = argv[1];
	
		if (argument == "--help" || argument == "-h")
		{
			_list_help_func();
			return 0;
		}
		else if (argument == "--time" || argument == "-t")
		{
			calcpq_bench();
			//std::cout << "LOL" << std::endl;
			return 0;
		}
		else if (argument == "--check-status" || argument == "-cs")
		{
			std::thread thread_progress(progress_of_run);
			std::thread thread_bench(calcpq_bench);
			thread_progress.join();
			thread_bench.join();
			return 0;
		}
		
		else if (argument == "--overclocking" || argument == "-oc")
		{
			calcpq_bench_realtime_overclocking();
			return 0;
		}
		else
		{
			std::cout << "Error: \"" << argument << "\" parameter not found. Type 'pqbench -h' for help." << std::endl;
			return -1;
		}
	
	}

	else if (argument == " " && argc == 1)
	{
		calcpq_bench();
		//std::cout << "LOL2" << std::endl;
	}


}








/*void stress() // coming soon!
{
	double p = 1276.5635;
	double q = 867.3649;

	
	while (true)
	{	
		quotient = -(p / 2);
		
		sqroot_of = sqrt((((p / 2) * (p / 2)) - q));

		zero_point_left = quotient - sqroot_of;
		zero_point_right = quotient + sqroot_of;
		
		p += 1276.4343757;
		q += 867.653543376;

		logvalue_left = log10(log10(zero_point_left) * log10(zero_point_left));
		logvalue_right = log10(log10(zero_point_right) * log10(zero_point_left));


		sqrlogvalue_left = logvalue_left * logvalue_right;
		sqrlogvalue_right = logvalue_right * logvalue_left;


		

	}
	

}*/


/*void progress_bar(long double current_progress)
{

	bar = &progressbar;

	if (current_progress < 10.0)
	{
		progressbar = "[          ]";
	}
	else if (current_progress > 10.0 && current_progress < 20.0)
	{
		progressbar = "[=         ]";
	}
	else if (current_progress > 20.0 && current_progress < 30.0)
	{
		progressbar = "[==        ]";
	}
	else if (current_progress > 30.0 && current_progress < 40.0)
	{
		progressbar = "[===       ]";
	}
	else if (current_progress > 40.0 && current_progress < 50.0)
	{
		progressbar = "[====      ]";
	}
	else if (current_progress > 50.0 && current_progress < 60.0)
	{
		progressbar = "[=====     ]";
	}
	else if (current_progress > 60.0 && current_progress < 70.0)
	{
		progressbar = "[======    ]";
	}
	else if (current_progress > 70.0 && current_progress < 80.0)
	{
		progressbar = "[=======   ]";
	}
	else if (current_progress > 80.0 && current_progress < 90.0)
	{
		progressbar = "[========  ]";
	}
	else if (current_progress > 90.0 && current_progress < 100.0 && current_progress < 99.9)
	{
		progressbar = "[========= ]";
	}
	else if (current_progress <= 100.0)
	{
		progressbar = "[==========]";
	}
}*/
