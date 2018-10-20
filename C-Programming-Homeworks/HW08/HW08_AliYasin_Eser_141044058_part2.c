/*****************************************************************
 *                                                               *
 * HW08 P2                                                       *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 18.04.2015                                      *
 *                                                               *
 ****************************************************************/
 /*Fonksiyonlarin ve kutuphanelerin tanimlanmasi*/
#include <stdio.h>
#include <string.h>
#define NAME_SIZE 30	/*Isim buyuklugu*/
#define SNAME_SIZE 30	/*Soyisim buyuklugu*/
#define SIZE 20	/*Cikti icin string boyutu*/
#define ARRAY_SIZE 10	/*Array'lerin eleman sayisi*/
#define TRUE 1
#define FALSE 0
/*Aylarin tip olarak tanimlanmasi*/
typedef enum
	{JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
	 AUGUST, SEPTEMBER, OCTOBER, NOVERMBER, DECEMBER
	} Months_t;
/*Cinsiyetin tip olarak tanimlanmasi*/
typedef enum
		{MALE, FEMALE
		} Gender_t;
/*Zamanin tip olarak tanimlanmasi*/
typedef struct
		{int hour,
			 minute;
		} Time_t;
/*T.C. numaralarinin tip olarak tanimlanmasi*/
typedef struct { 
		int first_half,
			second_half;
		} TCId_no_t;
		
/*Randevu alanlarin bilgilerini barindiracak tip*/
typedef struct { 
		TCId_no_t id_no;
		char name[NAME_SIZE];
		char surname[SNAME_SIZE];
		Gender_t gender;
		} People_t;
		
/*Zamanin yildan gune kadar olan kismini barindiracak tipin tanimlanmasi*/		
typedef struct
		{
		int year;
		Months_t month;
		int day;
		Time_t time;
		} Date_t;
/*Randevularin tek tip olarak tanimlanmasi*/
typedef struct
		{
			People_t people;
			Date_t date;
		}Appointment_t;
		

/*Fonksiyonlarin tanimlanmasi*/
int get_people(const char *file_name, People_t people[], int max_size);
int get_appointments(const char *file_name,
 Appointment_t appointments[], int max_size);
void write_names(Appointment_t appointments[], 
int size_app, const People_t people[], int size_people);
int check_appointments(Appointment_t appointments[], int size);
void sort_appointments(Appointment_t appointments[], int size);
void write_appointments(const char *file_name,
 Appointment_t appointments[], int size);

int
main()
{
	/*Girdi ve cikti dosyalarinin string olarak tanimlanmasi*/
	const char people[SIZE] = "People.txt";
	const char appointment[SIZE] = "AppointmentReqs.txt";
	const char last_appointment[SIZE] = "Appointments.txt";
	/*Kisiler ve randevularin array'i*/
	People_t people_arr[ARRAY_SIZE];
	Appointment_t appointment_arr[ARRAY_SIZE];
	/*Size degerleri*/
	int num_people, num_appointment, last_app;
	
	num_people = get_people(people, people_arr, ARRAY_SIZE);
	
	num_appointment = get_appointments
	( appointment, appointment_arr, ARRAY_SIZE );
	
	write_names( appointment_arr, num_appointment, people_arr, num_people );
	
	last_app = check_appointments( appointment_arr, num_appointment );
	
	write_appointments( last_appointment, appointment_arr, last_app );
	
	return 0;
}
/*Kisilerin bilgilerinin dosyadan alir ve array'e atar*/
int get_people(const char *file_name, People_t people[], int max_size)
{
	int count;
	char temp_gender;
	int status=0;
	FILE* iptr;
	/*Dosyayi acar, acamazsa hata verir*/
	if((iptr = fopen( file_name, "r" )) == FALSE)
		printf("People.txt has couln't open to read.Don't trust the output!");
	
	/*EOF okumaz ve alabileceginden fazla almamis ise array'e atar*/
	for(count=0;
	 (count < max_size) && (status != EOF); 
	 count++) 
	{
		status = fscanf( iptr, "%5d%6d %s %s %c", 
		&(people[count].id_no.first_half), &(people[count].id_no.second_half),
		people[count].name, people[count].surname, &temp_gender );
			 /*Cinsiyet icin ekleme*/
			if( status != EOF )
				if( temp_gender == 'M' )
			 		people[count].gender = MALE;
			 	else
			 		people[count].gender = FEMALE; 
	}
	/*Dosyanin kapatilmasi*/
	fclose(iptr);
	/*Son durumda update ile count arttigindan count-1 dondurulur*/
	return count-1;
}

/*Randevulari dosyadan okuyup array'e yazar*/
int get_appointments(const char *file_name, 
Appointment_t appointments[], int max_size)
{
	int temp_month;	/*Aylari atamak icin gecici degisken*/
	int count;
	int status=0;
	FILE* iptr;
	/*Dosyayi acar, acamazsa hata verir*/
	if((iptr = fopen( file_name, "r" )) == FALSE)
	{
		printf("AppointmentReqs.txt has couldn't open to read. ");
		printf("Don't trust the output!\n");
	}
	
	for(count=0;
	 (count < max_size) && (status != EOF); 
	 count++) 
		{
			status = fscanf( iptr, "%5d%6d %d %d %d %d:%d",
			 &(appointments[count].people.id_no.first_half),
			&(appointments[count].people.id_no.second_half),
			 &(appointments[count].date.year), &temp_month,
			&(appointments[count].date.day), 
			&(appointments[count].date.time.hour),
			 &(appointments[count].date.time.minute) );
			 		
			 appointments[count].date.month = (Months_t)temp_month;		
		}
	
	/*Dosyanin kapatilmasi*/
	fclose(iptr);
	/*Son durumda update ile count arttigindan count-1 dondurulur*/
	return count-1;
}


void write_names(Appointment_t appointments[], int size_app,
 const People_t people[], int size_people)
{
	int count;
	int roundc;
	/*Hangi array buyukse ona gore arama yapar, kucuk olani secer*/
	if( size_app > size_people )
	{
		for(count=0; count < size_people; count++)	
			for( roundc=0; roundc < size_app ; roundc++)
				if( appointments[roundc].people.id_no.first_half ==
				 people[count].id_no.first_half &&
				 appointments[roundc].people.id_no.second_half ==
				 people[count].id_no.second_half) 
				 
					appointments[roundc].people = people[count];
	}
	else
	{
		for(count=0; count < size_app; count++)	
			for( roundc=0; roundc < size_people ; roundc++)
			{
				if( appointments[count].people.id_no.first_half == 
				people[roundc].id_no.first_half &&
				appointments[count].people.id_no.second_half == 
				people[roundc].id_no.second_half) 
				
					appointments[count].people = people[roundc];			
			}	
	}	
}
/*Randevulari zamana gore siralar*/
void sort_appointments(Appointment_t appointments[], int size)
{
	Appointment_t temp;	/*Randevu degistirmek icin gecici deger*/
	int count;
	
	for( count=0; count < size-1; count++ )
		if(  appointments[count].date.year >= 
		appointments[count+1].date.year &&
		appointments[count].date.month >= appointments[count+1].date.month &&
		appointments[count].date.day >= appointments[count+1].date.day   &&
		appointments[count].date.time.hour >= 
		appointments[count+1].date.time.hour &&
		appointments[count].date.time.minute >= 
		appointments[count+1].date.time.minute
		)
		{
			temp = appointments[count];
			appointments[count] = appointments[count+1];
			appointments[count+1] = temp;
		}
	
}
/*Randevularin cakismasini onler, cakisan varsa ilk sirali olani alir*/
int check_appointments(Appointment_t appointments[], int size)
{
	int i,j, count;
	
	for(  i=size-1; i >= 1; i--)
	{
		for( j = i-1 ; j >= 0  ; j--)	
		{
			if(  appointments[i].date.year == appointments[j].date.year &&
			appointments[i].date.month == appointments[j].date.month &&
			appointments[i].date.day == appointments[j].date.day   &&
			appointments[i].date.time.hour == appointments[j].date.time.hour &&
			appointments[i].date.time.minute == 
			appointments[j].date.time.minute 
			)
			{
				for( count = i; count <= size-1; count++)	
					appointments[count] = appointments[count+1];
					size--;
			}
		}
	}
	/*Son degerin cakisan olmasi sebebiyle size-1 dondurulur*/
	return size-1;	
}
/*Randevulari dosyaya yazar*/
void write_appointments(const char *file_name,
 Appointment_t appointments[], int size)
{
	int i;	
	/*Dosyayi acar, acilmazsa hata verir*/
	FILE* optr;
	if((optr = fopen( file_name, "w" )) == FALSE)
	{
		printf("Appointment.txt has couldn't open to write. ");
		printf("Don't trust the output!\n");
	}
	/*Cinsiyete gore farkli cikti verir*/
	for( i=0; i <= size; i++ )
	{
		if(appointments[i].date.time.minute == 30 ||
		 appointments[i].date.time.minute== 00)
		{
			if( appointments[i].people.gender == MALE )
			{
				fprintf( optr,"%d %d %d %d:%d %d%d %s %s M\n", 
				appointments[i].date.year,
				 appointments[i].date.month, appointments[i].date.day,
				appointments[i].date.time.hour, 
				appointments[i].date.time.minute, 
				appointments[i].people.id_no.first_half,
				 appointments[i].people.id_no.second_half,
				appointments[i].people.name, appointments[i].people.surname);
			}
			else
			{
				fprintf(optr, "%d %d %d %d:%d %d%d %s %s F\n", 
				appointments[i].date.year, appointments[i].date.month,
				 appointments[i].date.day,
				appointments[i].date.time.hour,
				 appointments[i].date.time.minute, 
				appointments[i].people.id_no.first_half,
				 appointments[i].people.id_no.second_half,
				appointments[i].people.name, appointments[i].people.surname);
			}
		}
	}
	
	fclose(optr);
}

/*###########################################################################*/
/*              End of HW08_AliYasin_Eser_141044058_part2.c                  */
/*###########################################################################*/
