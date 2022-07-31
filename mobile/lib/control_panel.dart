import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:mobile/services/authentication_service.dart';
import 'package:provider/provider.dart';

class ControlPanel extends StatefulWidget {
  const ControlPanel({Key? key}) : super(key: key);

  @override
  ControlPanelState createState() => ControlPanelState();
}

class ControlPanelState extends State<ControlPanel> {
  Future<http.Response> changeMode(mode) async {
    print("making post request");
    final res = await http.post(Uri.parse("http://127.0.0.1:5000/"),
        headers: <String, String>{'Content-Type': 'application/json'},
        body: jsonEncode(<String, String>{"mode": mode}));
    // final res = await http.get(Uri.parse("http://127.0.0.1:5000/"));

    print(res.body);
    if (res.statusCode != 200) {
      throw Exception("did not change mode successtullly");
    }
    return res;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Home"),
      ),
      body: Center(
          child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
        ElevatedButton(
            onPressed: () => context.read<AuthenticationService>().signOut(),
            child: const Text("Sign Out")),
        ElevatedButton(
            onPressed: () => changeMode("wheel"), child: const Text("mode 1")),
        ElevatedButton(
            onPressed: () => changeMode("rainbow"),
            child: const Text("mode 2")),
        ElevatedButton(
            onPressed: () => changeMode("single"), child: const Text("mode 3")),
      ])),
    );
  }
}
