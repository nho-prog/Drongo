DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/update_esb_request.c \
../db_access/has_transport_config.c ../db_access/has_transform_config.c \
../db_access/insert_to_esb_request.c ../db_access/fetch_new_esb_request.c\
../db_access/finish_with_error.c
ADAPTER = ../adapter/call_destination_service.c ../adapter/transform.c

XML_HANDLER = ../bmd_handler/xml_handler.c ../bmd_handler/is_bmd_valid.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: esb.c valid.o
	gcc esb.c ${XML_HANDLER} ${SQL_API} -o esb ${DB_ACCESS} ${INCLUDE} ${ADAPTER} -lcurl
valid.o: ${XML_HANDLER} ../bmd_handler/bmd.h
	gcc -c ${DB_ACCESS} ${XML_HANDLER} ../bmd_handler/is_bmd_valid.c ${INCLUDE} ${ADAPTER} -lcurl
clean:
	rm *.o esb *.json
