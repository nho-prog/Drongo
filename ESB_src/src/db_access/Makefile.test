DB_ACCESS =  ./insert_to_esb_request.c ./get_active_route_id.c ./has_transport_config.c ./has_transform_config.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`

fetch: fetch_transport_config.c
	gcc  ${DB_ACCESS} fetch_transport_config.c -o fetch ${INCLUDE}
#test: test_db_access.c
#	gcc  ${DB_ACCESS} ${XML_HANDLER} test_db_access.c -o test ${INCLUDE} ../test/munit.c 

clean:
	rm fetch