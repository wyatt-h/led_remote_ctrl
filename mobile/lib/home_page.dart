import 'package:camera/camera.dart';
import 'package:flutter/material.dart';
import 'package:mobile/TakePictureScreen.dart';
import 'package:mobile/control_panel.dart';

class HomePage extends StatefulWidget {
  @override
  HomePageState createState() => HomePageState();
}

class HomePageState extends State<HomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Home"),
        ),
        body: Center(
          child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                ElevatedButton(
                    onPressed: () => Navigator.pushNamed(context, "/camera"),
                    child: Text("Camera")),
                ElevatedButton(
                    onPressed: () => Navigator.pushNamed(context, "/control"),
                    child: Text("Control Panel")),
              ]),
        ));
  }
}
