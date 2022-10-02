source create_schema.sql;

INSERT INTO routes (sender,destination,message_type,is_active)
VALUES
  ('4ac26b10-f658-11ea-adc1-0242ac120002','4ac26c14-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac26e80-f658-11ea-adc1-0242ac120002','4ac271fa-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac27466-f658-11ea-adc1-0242ac120002','4ac2752e-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac27984-f658-11ea-adc1-0242ac120002','4ac27a42-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac27c68-f658-11ea-adc1-0242ac120002','4ac27d26-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac280aa-f658-11ea-adc1-0242ac120002','4ac28172-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac283b6-f658-11ea-adc1-0242ac120002','4ac2860e-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac28848-f658-11ea-adc1-0242ac120002','4ac28910-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac28d16-f658-11ea-adc1-0242ac120002','4ac28dde-f658-11ea-adc1-0242ac120002','CreditReport',b'1'),
  ('4ac29018-f658-11ea-adc1-0242ac120002','4ac290d6-f658-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('4ac29482-f658-11ea-adc1-0242ac120002','4ac29536-f658-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('4ac298ec-f658-11ea-adc1-0242ac120002','4ac299e6-f658-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45b4d0-f65b-11ea-adc1-0242ac120002','6f45b728-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45b994-f65b-11ea-adc1-0242ac120002','6f45ba7a-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45be9e-f65b-11ea-adc1-0242ac120002','6f45bf70-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45c33a-f65b-11ea-adc1-0242ac120002','6f45c40c-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45c646-f65b-11ea-adc1-0242ac120002','6f45c70e-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1'),
  ('6f45cad8-f65b-11ea-adc1-0242ac120002','6f45cba0-f65b-11ea-adc1-0242ac120002','CURR_EXCHG',b'1');

INSERT INTO transform_config(route_id,config_key,config_value) 
VALUES 
   (1,"IFSC","No Transform"),
   (2,"IFSC","No Transform"),
   (3,"IFSC","No Transform"),
   (4,"IFSC","No Transform"),
   (5,"IFSC","No Transform"),
   (6,"IFSC","No Transform"),
   (7,"IFSC","No Transform"),
   (8,"IFSC","No Transform"),
   (9,"IFSC","No Transform"),
   (10,"CURR_EXCHG","No Transform"),
   (11,"CURR_EXCHG","No Transform"),
   (12,"CURR_EXCHG","No Transform"),
   (13,"CURR_EXCHG","No Transform"),
   (14,"CURR_EXCHG","No Transform"),
   (15,"CURR_EXCHG","No Transform"),
   (16,"CURR_EXCHG","No Transform"),
   (17,"CURR_EXCHG","No Transform"),
   (18,"CURR_EXCHG","No Transform");

INSERT INTO transport_config(route_id,config_key,config_value) 
VALUES 
   (1,"API_URL","https://ifsc.razorpay.com/"),
   (2,"API_URL","https://ifsc.razorpay.com/"),
   (3,"API_URL","https://ifsc.razorpay.com/"),
   (4,"API_URL","https://ifsc.razorpay.com/"),
   (5,"API_URL","https://ifsc.razorpay.com/"),
   (6,"API_URL","https://ifsc.razorpay.com/"),
   (7,"API_URL","https://ifsc.razorpay.com/"),
   (8,"API_URL","https://ifsc.razorpay.com/"),
   (9,"API_URL","https://ifsc.razorpay.com/"),
   (10,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (11,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (12,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (13,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (14,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (15,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (16,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (17,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/"),
   (18,"API_URL","https://v6.exchangerate-api.com/v6/41ea26638eb03e28aad2512e/latest/");

