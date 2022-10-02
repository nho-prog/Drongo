DB_ACCESS =  ./insert_to_esb_request.c ./get_active_route_id.c ./has_transport_config.c ./has_transform_config.c \
./db_connect.c ./select_all_transport_config.c \
./select_active_routes.c ./update_esb_request.c ./fetch_transport_config.c \
./fetch_new_esb_request.c ./fetch_transform_config.c
XML_HANDLER = ../bmd_handler/xml_handler.c ../bmd_handler/is_bmd_valid.c
ADAPTER = ../adapter/transform.c ../adapter/call_destination_service.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: test_db_access.c
	gcc  ${DB_ACCESS} ${XML_HANDLER} ${ADAPTER} test_db_access.c -o test ${INCLUDE} ../test/munit.c -lcurl
clean:
	rm test
