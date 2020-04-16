#ifndef STTDATA_H
#define STTDATA_H

#define TAILLE_FRAME 2048
#define MAX_SENSORS 10
#define MAX_DATA 12

struct sttdata
{
	int Num;
	char TypeRoot[50];
	char Id[50];
	time_t Date;

	struct sensor_s
	{
		const char *Type;
		const char *Source;

		struct data_s
		{
			const char *key;
			double value;
			const char *unit;
		} data[MAX_DATA];
		int nbdata;
	} sensors[MAX_SENSORS];
	int nbsensors;

};
#endif
