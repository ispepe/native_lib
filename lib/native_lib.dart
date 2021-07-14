// You have generated a new plugin project without
// specifying the `--platforms` flag. A plugin project supports no platforms is generated.
// To add platforms, run `flutter create -t plugin --platforms <platforms> .` under the same
// directory. You can also find a detailed instruction on how to add platforms in the `pubspec.yaml` at https://flutter.dev/docs/development/packages-and-plugins/developing-packages#plugin-platforms.

import 'dart:async';
import 'dart:ffi';
import 'dart:io';

import 'package:flutter/services.dart';

DynamicLibrary nativeLib = Platform.isAndroid
    ? DynamicLibrary.open("libnative_add.so")
    : DynamicLibrary.process();

class NativeLib {
  static const MethodChannel _channel = const MethodChannel('native_lib');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  /// 碰见异常了，再打开一次，兼容安卓旧版本
  Future<void> applyWorkaroundToOpenSqlite3OnOldAndroidVersions() async {
    if (!Platform.isAndroid) return;

    try {
      nativeLib = DynamicLibrary.open('libnative-lib.so');
    } on ArgumentError {
      // Ok, the regular approach failed. Try to open sqlite3 in Java, which seems
      // to fix the problem.
      await _channel.invokeMethod('doesnt_matter');

      // Try again. If it still fails we're out of luck.
      nativeLib = DynamicLibrary.open('libnative-lib.so');
    }
  }
}
