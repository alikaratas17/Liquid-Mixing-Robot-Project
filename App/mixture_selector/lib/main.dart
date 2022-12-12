import 'package:flutter/material.dart';
import 'dart:convert';
import 'my_key.dart' as my_key;
import 'package:http/http.dart' as http;


void main()=> runApp(MyApp());
class MyApp extends StatelessWidget{
  var drinks = ["Lemon Juice", "Orange Juice", "Grenadine Juice", "Apple Juice"];
  var amounts = [0.0,0.0,0.0,0.0];
  @override
  Widget build(BuildContext context){
    return MaterialApp(title: 'Select a Mixture',
    home:Scaffold(appBar: AppBar(title: Text('Why is this title different from prev?')),body: Column(children: [
      Text('Please Select one of below'),
      ElevatedButton(onPressed: opt1_func, child: Text('Option 1')),
      ElevatedButton(onPressed: opt2_func, child: Text('Option 2')),
      ElevatedButton(onPressed: opt3_func, child: Text('Option 3')),
      ElevatedButton(onPressed: opt4_func, child: Text('Option 4')),
      ElevatedButton(onPressed: send_mixture, child: Text('Make Mixture')),
    ]),));
  }
void send_mixture() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  double total = amounts.reduce((v, e) => v+e)+1e-12; // Check if this is valid to get sum
  var percentages = [0,0,0,0];
  for (int i = 0; i< 3; i++)
    percentages[i] = (100.0*amounts[i]/total).round();
  percentages[3] = 100 - percentages.reduce((v, e) => v+e); // Check if this is valid to get sum
  String mixture = percentages[0].toString()+','+percentages[1].toString()+','+percentages[2].toString()+','+percentages[3].toString(); // Format should be 4 ints (percentages) separated by ','
  final response = await http.post(Uri.parse(my_url),body:{'value':mixture});
  print(response.statusCode.toString()); // For debugging
}
}

void opt1_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 1";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt2_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 2";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt3_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 3";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt4_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 4";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
/*
void main()=> runApp(const MyApp());
class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or simply save your changes to "hot reload" in a Flutter IDE).
        // Notice that the counter didn't reset back to zero; the application
        // is not restarted.
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;

  void _incrementCounter() {
    setState(() {
      // This call to setState tells the Flutter framework that something has
      // changed in this State, which causes it to rerun the build method below
      // so that the display can reflect the updated values. If we changed
      // _counter without calling setState(), then the build method would not be
      // called again, and so nothing would appear to happen.
      _counter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    return Scaffold(
      appBar: AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: Text(widget.title),
      ),
      body: Center(
        // Center is a layout widget. It takes a single child and positions it
        // in the middle of the parent.
        child: Column(
          // Column is also a layout widget. It takes a list of children and
          // arranges them vertically. By default, it sizes itself to fit its
          // children horizontally, and tries to be as tall as its parent.
          //
          // Invoke "debug painting" (press "p" in the console, choose the
          // "Toggle Debug Paint" action from the Flutter Inspector in Android
          // Studio, or the "Toggle Debug Paint" command in Visual Studio Code)
          // to see the wireframe for each widget.
          //
          // Column has various properties to control how it sizes itself and
          // how it positions its children. Here we use mainAxisAlignment to
          // center the children vertically; the main axis here is the vertical
          // axis because Columns are vertical (the cross axis would be
          // horizontal).
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            const Text(
              'You have pushed the button this many times:',
            ),
            Text(
              '$_counter',
              style: Theme.of(context).textTheme.headline4,
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}
*/