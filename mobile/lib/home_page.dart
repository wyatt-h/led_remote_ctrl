import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

class HomePage extends StatelessWidget {
  const HomePage({Key? key}) : super(key: key);

  Future<http.Response> changeMode(mode) async {
    final res = await http.post(Uri.parse("http://localhost:3000"),
        headers: {"Content-Type": "application/json"}, body: {"mode": mode});

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
