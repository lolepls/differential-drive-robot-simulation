#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <unistd.h>
#include <time.h>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <iostream>


//// -- ENCODER 20 Hz by TeamAngio - Daniele Nicolò/Gioele Mombelli -- Robotics 2018////

double vel_dx;  
double vel_sx;


namespace gazebo 
{
	class encoder_plugin : public ModelPlugin 
	{

		public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/) 
		{
			
    
			this->model = _parent; 
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&encoder_plugin::OnUpdate, this));
			
			
		}
			
		public: void OnUpdate()
		{
			
			//istante_attuale è l'orologio della simulazione.
			//intervallo è il tempo trascorso tra ora e l'ultima misura della velocità (avvenuta a t_ultima_misura), in secondi.

			auto istante_attuale = gazebo::physics::get_world()->GetSimTime();
			auto intervallo = (istante_attuale - this->t_ultima_misura).Double();

			// Se il tempo passato è <0 significa che la simulazione è stata resettata. Il caso va considerato.
			if (intervallo < 0)
			{
  			this->t_ultima_misura = istante_attuale;
  			return;
			}

			// Se non è passato abbastanza tempo, non dobbiamo misurare la velocità: quindi la funzione ritorna.

			if (intervallo < 0.05){  //[0.05 è la frequenza di misurazione, corrispondente a 20Hz.]
  			return;
			}

			//Se è ora di misurare la velocità eseguiamo questo.

			this->t_ultima_misura = istante_attuale;

			this->joint1_ = this->model->GetJoint("Ruota dx"); 
			this->joint2_ = this->model->GetJoint("Ruota sx");
			vel_dx = this->joint1_->GetVelocity(0);	//[GetVelocity fornisce velocità della ruota.]
			vel_sx = this->joint2_->GetVelocity(0);


				printf ("Velocità ruota destra: %f rad/s\n", vel_dx);
				printf ("Velocità ruota sinistra: %f rad/s\n", vel_sx);
				printf("Frequenza dell'encoder: %f Hz\n", 1/intervallo);						
				printf("\n------\n");

			
				
			}

				
		

		


private: physics::ModelPtr model; 
private: event::ConnectionPtr updateConnection;
private: physics::JointPtr joint1_;
private: physics::JointPtr joint2_;
//Indica l'ultima volta che è stata misurata la velocità.
private: gazebo::common::Time t_ultima_misura;

};

GZ_REGISTER_MODEL_PLUGIN(encoder_plugin)
}



