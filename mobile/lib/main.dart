import 'package:camera/camera.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:mobile/TakePictureScreen.dart';
import 'package:mobile/home_page.dart';
import 'package:mobile/register_page.dart';
import 'package:mobile/services/authentication_service.dart';
import 'package:mobile/control_panel.dart';
import 'package:mobile/login_page.dart';
import 'package:provider/provider.dart';
import 'firebase_options.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(options: DefaultFirebaseOptions.currentPlatform);
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  MyAppState createState() => MyAppState();
}

class MyAppState extends State<MyApp> {
  late CameraDescription firstCamera;

  @override
  void initState() {
    super.initState();
    initializeCam();
  }

  Future<void> initializeCam() async {
    WidgetsFlutterBinding.ensureInitialized();
    final cameras = await availableCameras();
    print(cameras);
    firstCamera = cameras.first;
  }

  @override
  Widget build(BuildContext context) {
    return MultiProvider(
      providers: [
        Provider<AuthenticationService>(
            create: (_) => AuthenticationService(FirebaseAuth.instance)),
        StreamProvider(
          create: (context) =>
              context.read<AuthenticationService>().authStateChanges,
          initialData: null,
        )
      ],
      child: MaterialApp(
        title: "Control Your LED",
        initialRoute: '/',
        routes: {
          '/': (context) => const AuthenticationWrapper(),
          '/login': (context) => const LoginPage(),
          '/register': (context) => const RegisterPage(),
          '/camera': (context) => TakePictureScreen(camera: firstCamera),
          '/control': (context) => const ControlPanel(),
        },
        // home: const AuthenticationWrapper(),
      ),
    );
  }
}

class AuthenticationWrapper extends StatelessWidget {
  const AuthenticationWrapper({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final firebaseUser = context.watch<User?>();

    if (firebaseUser != null) {
      return HomePage();
    }

    return const LoginPage();
  }
}
