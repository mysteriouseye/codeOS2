typedef struct fat32part{
	uint8_t disk;
	uint16_t part_sect;
	uint8_t sectors_per_cluster;
	uint32_t root_dir_sect;
	uint32_t root_dir_clust;
	uint32_t cluster_begin_sect;
	uint8_t num_fats;
	uint32_t sectors_per_fat;
	uint16_t reserved_sectors;
} fat32part;

bool isPartitionFAT32(int disk, int sect);
fat32part getFat32Part(int disk, int part_sect);
uint32_t clusterToLBA(uint32_t cluster);
uint32_t clusterToLBAOther(fat32part p, uint32_t cluster);
void setCurrentFat32part(fat32part p);
void listDir(uint32_t cluster);
uint32_t getClusterOfEntry(uint8_t *entry);
#include "fat32.c"