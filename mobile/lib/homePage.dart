import 'package:flutter/material.dart';
import 'package:mobile/authentication_service.dart';
import 'package:provider/provider.dart';

class homePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Home"),
      ),
      body: Center(
          child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
        Text("Welcome to the APP!"),
        ElevatedButton(
            onPressed: () {
              context.read<AuthenticationService>().signOut();
            },
            child: Text("Sign Out"))
      ])),
    );
  }
}
