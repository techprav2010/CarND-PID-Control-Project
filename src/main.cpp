#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main()
{
  uWS::Hub h;

  PID pid;
  // TODO: Initialize the pid variable.
//    void PID::Init(double P, double I, double D)
//    pid.Init(1, 1, 1);//failed
//    pid.Init(1, 0, 0);//failed
//    pid.Init(1, 0, 1);//failed
//    pid.Init(1, 1, 0);//failed
//    pid.Init(1, .1, 1);//failed
//    pid.Init(.1, .1, 1);//failed
//    pid.Init(.1, .01, 1);//failed
//    pid.Init(.1, .01, .1);//failed
//    pid.Init(.1, .01, 2);//failed
//    pid.Init(.1, .01, 3);//failed
//    pid.Init(.1, .01, 4);//passing
//    pid.Init(.1, .001, 4);//failed
//    pid.Init(.1, .009, 4);//passing
//    pid.Init(.2, .009, 4);//passing
//    pid.Init(.2, .004, 3);//failed
//    pid.Init(.2, .0004, 1 );//passing
//    pid.Init(.12, .25, .00001);//failed
//    pid.Init(.1, .0001, 1.9);  //failed
//    pid.Init(.1, .0001, 2.9); //failed
//    pid.Init(.2, .0001, 1.9); //passing
//    pid.Init(.2, .0002, 1.9); //passing
//    pid.Init(.1, .0001, .6); //good 1
//    pid.Init(.1, .0001, .9); //good 2
//    pid.Init(.2, .0002, .3); //  0 --zigzag FAILED
//    pid.Init(.2, .0002, .9); //  still --zigzag
//    pid.Init(.2, .0002, 2.0); //   2 - close to edge of the road
//    pid.Init(1.2, .0002, 2.0);  // zigzag at curves  FAILED
//    pid.Init(1.2, .0002, 1.0);  // zigzag at curves  FAILED
//    pid.Init(1.2, .002, 1.0);   // zigzag at curves  FAILED
//    pid.Init(.05, .0002, 1.0); //  curves  FAILED
//    pid.Init(.05, .0002, .2); //  still bad on curves  FAILED
//    pid.Init(.05, .00002, .2); //  still bad on curves  FAILED
//    pid.Init(.05, .00002, .9); // still bad on curves  FAILED
//    pid.Init(.05, .002, .9); // zigzag  FAILED
//    pid.Init(.5, .002, .9); // more zigzag  FAILED
//    pid.Init(.5, .002, 2.0); // zigzag  but close to center FAILED
//    pid.Init(.5, .002, 3.0); // zigzag  but close to center FAILED
//    pid.Init(1.5, .002, 3.0); // zigzag   FAILED
//    pid.Init(1.5, .002, .9); // zigzag   FAILED
//    pid.Init(1.5, .00002, .9); // zigzag worst  FAILED
//    pid.Init(1.5, .0002, .9); // zigzag   FAILED
//    pid.Init(.5, .0002, .9); // still zigzag    FAILED
//    pid.Init(.5, .0002, .2); // still zigzag    FAILED
//    pid.Init(.5, .0001, .2); // still zigzag    FAILED
//    pid.Init(.2, .0001, .2); // still zigzag    FAILED
//    pid.Init(.2, .0001, .9); // still zigzag    FAILED
//    pid.Init(.1, .0001, .9); //  -- but still close to curve
//    pid.Init(.05, .0001, .9); //  -- but still close to curve FAILED
//    pid.Init(.05, .0001, .5); //  -- but still close to curve FAILED
//    pid.Init(.05, .0005, .5); //  -- but still close to curve FAILED
//    pid.Init(.05, .001, .5); //  -- but still close to curve FAILED
//    pid.Init(.08, .001, .5); //  -- but still close to curve FAILED
//    pid.Init(.08, .007, .5); //worst --   FAILED
//    pid.Init(.8, .007, .5);  //worst --   FAILED
//    pid.Init(.8, .007, 2.5);  //bettter --   FAILED
//    pid.Init(.8, .007, 1.5);  //worst --   FAILED
//    pid.Init(.8, .0007, 1.5);  //worst --   FAILED
//    pid.Init(.8, .00007, 1.5);  //worst --   FAILED
//    pid.Init(1.8, .00007, 1.5);  //worst --   FAILED
//    pid.Init(.1, .0001, 1.5);  //better --   FAILED
//    pid.Init(.2, .0001, 1.5);  //passing
//    pid.Init(.25, .0001, 1.5);  //passing more jerks
//    pid.Init(.25, .0003, 1.5);  //passing smoothened
//    pid.Init(.25, .0005, 1.5);  //passing smoothened
//    pid.Init(.2, .0005, 1.5);  //passing smoothened
//    pid.Init(.2, .0006, 1.5);  //passing smoothened
//    pid.Init(.2, .0009, 1.5);  //passing smoothened
//    pid.Init(.2, .001, 1.5);  //passing smoothened
//    pid.Init(.2, .001, 2.5);  //passing smoothened
//    pid.Init(.2, .001, 3.0);  //passing smoothened
//    pid.Init(.15, .001, 3.0);  //passing
//    pid.Init(.15, .001, 2.0);  //passing
//    pid.Init(.2, .001, 2.0);  //passing smoothened best so far
//    pid.Init(.2, .002, 2.0);  //passing smoothened
//    pid.Init(.25, .002, 2.0);  //passing smoothened
//    pid.Init(.25, .003, 2.0);  //passing zigzag
//    pid.Init(.25, .003, .9);  //passing zigzag
//    pid.Init(.20, .005, .9);  //passing zigzag
//    pid.Init(.20, .005, 2.0);  //passing zigzag
//    pid.Init(.10, .005, 2.0);  //passing zigzag
//    pid.Init(.10, .005, 3.0);  //passing
//    pid.Init(.07, .005, 3.0);  //passing  zigzag
//    pid.Init(.07, .007, 3.0);  //failed  zigzag
//    pid.Init(.27, .007, 3.0);  //failed  zigzag
//    pid.Init(.8, .007, 3.0);  //failed  zigzag
//    pid.Init(.8, .009, 3.0);  //failed  zigzag
//    pid.Init(.8, .009, .9);  //failed  zigzag
//    pid.Init(.8, .0009, .9);  //failed  zigzag
//    pid.Init(.8, .0009, 3.9);  //failed  zigzag
//    pid.Init(.8, .01, 3.9);  //failed  zigzag
//    pid.Init(.2, .01, 3.9);  //passing
//    pid.Init(.2, .01, 1.9);  //failed  zigzag
//    pid.Init(.2, .01, 4.9);  //passing
//    pid.Init(.2, .01, 5.9);  //passing
//    pid.Init(.2, .02, 5.9);  //failed  zigzag
//    pid.Init(.3, .01, 5.9);  //passing
//    pid.Init(.5, .01, 5.9);  //passing
//    pid.Init(.1, .01, 5.9);  //passing
//    pid.Init(.1, .01, 5.9);  //passing
//    pid.Init(.2, .01, 8.9);  //passing
//    pid.Init(.2, .01, 1.0);  //passing  jerks
//    pid.Init(.2, .04, 1.0);  //failed
//    pid.Init(.1, .04, 1.0);  //failed
//    pid.Init(1.0, .04, 1.0);  //passing  jerks
//    pid.Init(1.0, .4, 1.0);  //failed
//    pid.Init(5.0, .4, 1.0);  //failed
//    pid.Init(5.0, .4, 5.0);    //passing  jerks
//    pid.Init(.5, .04, 5.0);    //failed
//    pid.Init(.5, .08, 5.0);    //failed
//    pid.Init(.5, .08, 3.0);    //failed
//    pid.Init(.5, .08, .9);    //failed
//    pid.Init(.1, .08, .9);    //failed
//    pid.Init(.1, .008, .9);    //failed
//    pid.Init(.1, .008, 2.9);    //failed
//    pid.Init(.1, .0008, 2.9); //failed smoothened
//    pid.Init(.2, .0008, 2.9); //passing smoothened
//    pid.Init(.3, .0008, 2.9); //passing
//    pid.Init(.2, .0008, 1.9); //passing smoothened
//    pid.Init(.2, .0006, 1.9); //passing smoothened
//    pid.Init(.2, .0004, 1.9); //passing smoothened
//    pid.Init(.2, .0004, .9); //passing
//    pid.Init(.2, .0002, .9); //passing
//    pid.Init(.2, .0001, .9); //passing
//    pid.Init(.2, .001, .9); //passing smoothened
//    pid.Init(.2, .001, 2.9); //passing
//    pid.Init(.2, .001, 3.9); //passing
//    pid.Init(.25, .001, 3.9); //passing
//    pid.Init(.2, .001, 2.0);  //passing
//    pid.Init(.2, .001, 3.0);  //passing
//    pid.Init(.2, .008, 3.0);  //passing
//    pid.Init(.25, .006, 2.5);  //passing
//    pid.Init(.25, .003, 2.5);  //passing
//    pid.Init(.2, .009, 2.5);  //passing
//    pid.Init(.2, .0009, 2.5);  //passing
//    pid.Init(.15, .002, 2.5);  //passing
//    pid.Init(.15, .001, 2.5);  //passing
//    pid.Init(.2, .004, 3.5);  //passing
//    pid.Init(.2, .01, 3.9);  //passing
//    pid.Init(.2, .001, 3.9);  //passing
//    pid.Init(.2, .001, 2.9);  //passing
//    pid.Init(.2, .007, 2.9);  //passing
//    pid.Init(.2, .007, 1.9);  //passing
//    pid.Init(.2, .009, 2.9);  //passing
//    pid.Init(.2, .009, 1.9);  //passing
//    pid.Init(.25, .003, 2.5); //passing
//    pid.Init(.25, .007, 4.5); //passing
//    pid.Init(.2, .006, 4.5); //passing
//    pid.Init(.2, .009, 4.5); //passing
//    pid.Init(.15, .009, 0.7); //failed
    pid.Init(.2, .009, 2.5); //passing



    h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double steer_value;
          /*
          * TODO: Calcuate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */

          pid.UpdateError(cte);

          // Update steering
          steer_value = pid.TotalError();
          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = .3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
