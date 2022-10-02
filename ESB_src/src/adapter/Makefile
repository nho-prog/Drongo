ADAPTER = ./email.c ./http_post.c ./transform.c ./call_destination_service.c
BMD = ../bmd_handler/is_bmd_valid.c ../bmd_handler/xml_handler.c 
DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/fetch_transport_config.c ../db_access/has_transform_config.c \
../db_access/has_transport_config.c ../db_access/finish_with_error.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test_adapter: test_adapter.c	
	gcc ${ADAPTER} ${BMD} ${DB_ACCESS} test_adapter.c -lcurl -o test ${INCLUDE} ../test/munit.c
