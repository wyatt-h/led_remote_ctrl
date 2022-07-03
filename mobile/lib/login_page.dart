import 'package:flutter/material.dart';
import 'package:mobile/registerPage.dart';
import 'package:mobile/services/authentication_service.dart';
import 'package:provider/provider.dart';

class LoginPage extends StatefulWidget {
  const LoginPage({Key? key}) : super(key: key);

  @override
  LoginPageState createState() => LoginPageState();
}

class LoginPageState extends State<LoginPage> {
  final _formKey = GlobalKey<FormState>();
  final emailController = TextEditingController();
  final passwordController = TextEditingController();

  @override
  void initState() {
    super.initState();
  }

  @override
  void dispose() {
    emailController.dispose();
    passwordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Login"),
        ),
        body: Form(
          key: _formKey,
          child: Column(mainAxisAlignment: MainAxisAlignment.center, children: <
              Widget>[
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
              child: TextFormField(
                autofocus: true,
                decoration: const InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: "Type in your email",
                    label: Text("Email")),
                controller: emailController,
                validator: (value) {
                  if (value == null || value.isEmpty) {
                    return "Please enter your email...";
                  }
                  return null;
                },
              ),
            ),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
              child: TextFormField(
                decoration: const InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: "Type in your password...",
                    label: Text("Password")),
                controller: passwordController,
                validator: (value) {
                  if (value == null || value.isEmpty) {
                    return "Please enter your password";
                  }
                  return null;
                },
              ),
            ),
            Padding(
                padding:
                    const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
                child: ElevatedButton(
                    onPressed: () {
                      if (_formKey.currentState!.validate()) {
                        context.read<AuthenticationService>().signIn(
                            email: emailController.text.trim(),
                            password: passwordController.text.trim());
                      }
                    },
                    child: const Text("Login"))),
            Padding(
                padding:
                    const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
                child: RichText(
                  text: TextSpan(
                      style: const TextStyle(fontSize: 15, color: Colors.black),
                      children: [
                        const TextSpan(text: "Doesn't have an account yet? "),
                        WidgetSpan(
                            child: GestureDetector(
                          onTap: () {
                            Navigator.pushNamed(context, '/register');
                          },
                          child: const Text(
                            "Register",
                            style: TextStyle(
                                color: Colors.blueAccent,
                                fontSize: 17,
                                fontWeight: FontWeight.bold),
                          ),
                        ))
                      ]),
                )),
          ]),
        ));
  }
}
