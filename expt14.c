#include <stdio.h>
// address conversion(virtual-physical): simulator for paging

int main() {
    int virtual_mem_size, page_size,b_page_size, virtual_address;
    int num_pages, page_number, offset;
    printf("Enter virtual address space in MB: ");
    scanf("%d", &virtual_mem_size);
    printf("Enter page size in KB: ");
    scanf("%d", &page_size);
    printf("Enter virtual address (in decimal): ");
    scanf("%d", &virtual_address);
    // Convert MB → KB
    virtual_mem_size = virtual_mem_size * 1024;

    // Number of pages(virtual pages)
    num_pages = virtual_mem_size / page_size;

    int page_table[num_pages];

    for (int i = 0; i < num_pages; i++) {
    page_table[i] = i;  // simple mapping
}
    b_page_size = page_size * 1024;  // KB → bytes
    // Calculate page number and offset
    page_number = virtual_address / b_page_size;
    offset = virtual_address % b_page_size;
    // Check page fault
    if (page_number >= num_pages || page_table[page_number] == -1) {
        printf("Page fault occurred!\n");
    } 
    else {
        int frame_number = page_table[page_number];
        int physical_address = frame_number * b_page_size + offset;
        printf("Page number: %d\n", page_number);printf("Offset: %d\n", offset);
        printf("Frame number: %d\n", frame_number);printf("Physical address: %d\n", physical_address);
    }
    return 0;
}