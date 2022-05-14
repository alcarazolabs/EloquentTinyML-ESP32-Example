#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h> //comment it if you're using 0.0.5 version

// sensor_model.h contains the array you exported from the previous step with xxd or tinymlgen
#include "sensor_model.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
// in future projects you may need to tweak this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 2*1024

//Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml; //uncomment it if you're using version 0.0.5

Eloquent::TinyML::TensorFlow::TensorFlow<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> tf; //comment it if you're using 0.0.5 version

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando modelo");
    tf.begin(sensor_model);
     Serial.println("Modelo iniciado");
}

void loop() {

      if (Serial.available () > 0) {
        float x = Serial.parseFloat ();
	      Serial.println("Reading..");
	      delay(2000);
		    //float x = 35.22; 
        float input[1] = { x };
        float predicted = tf.predict(input);
		    Serial.print("X = ");
        Serial.print(x);
        Serial.print("\t predicted: ");
        Serial.println(predicted);
        if(predicted > 0.50 ) {
          Serial.print("\t There is moisture: ");
        }else{
          Serial.print("\t drain water: ");
        }
    }
}


/*

If this is not the case and you expect multiple output from your model, you have to declare an output array.

float input[10] = { ... };
float output[5] = { 0 };

tf.predict(input, output);
*/
