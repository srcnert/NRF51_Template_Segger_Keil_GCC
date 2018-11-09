#ifndef __MY_FSTORAGE_H
#define	__MY_FSTORAGE_H

void my_fstorage_init(void);
void my_fstorage_read(uint32_t *data, uint16_t array_position);
void my_fstorage_write(uint32_t  data, uint16_t array_position);
void my_fstorage_erase(uint16_t num_pages);
void my_fstorage_erase_all(void);

#endif /* __MY_FSTORAGE_H */
