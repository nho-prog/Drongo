DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/has_transport_config.c ../db_access/has_transform_config.c \
../db_access/db_connect.c ../db_access/fetch_transport_config.c
XML_HANDLER = ./is_bmd_valid.c ./xml_handler.c
ADAPTER = ../adapter/transform.c ../adapter/call_destination_service.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
xml: xml_handler.c bmd.h
	gcc  ${DB_ACCESS} ${XML_HANDLER} ${ADAPTER} test_bmd.c -o test ${INCLUDE} ../test/munit.c -lcurl
clean:
	rm xml