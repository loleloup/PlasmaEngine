// MIT Licensed (see LICENSE.md).
#pragma once

namespace Plasma
{

// Window Events
namespace Events
{
DeclareEvent(OsMouseUp);
DeclareEvent(OsMouseDown);
DeclareEvent(OsMouseMove);
DeclareEvent(OsMouseScroll);
DeclareEvent(OsKeyDown);
DeclareEvent(OsKeyUp);
DeclareEvent(OsKeyRepeated);
DeclareEvent(OsKeyTyped);
DeclareEvent(OsDeviceChanged);
DeclareEvent(OsResized);
DeclareEvent(OsMoved);
DeclareEvent(OsClose);
DeclareEvent(OsFocusGained);
DeclareEvent(OsFocusLost);
DeclareEvent(OsPaint);
DeclareEvent(OsMouseFileDrop);
DeclareEvent(OsWindowMinimized);
DeclareEvent(OsWindowRestored);

// Checking if we're over one of the grip borders of a window.
DeclareEvent(OsWindowBorderHitTest);

} // namespace Events

extern const String cOsKeyboardEventsFromState[3];

class KeyboardEvent;
class KeyboardTextEvent;
class OsMouseEvent;
class OsMouseDropEvent;
class OsWindowEvent;
class OsShell;

class OsInputHook
{
public:
  virtual void HookKeyboardEvent(KeyboardEvent& event) = 0;
  virtual void HookKeyboardTextEvent(KeyboardTextEvent& event) = 0;
  virtual void HookMouseEvent(OsMouseEvent& event) = 0;
  virtual void HookMouseDropEvent(OsMouseDropEvent& event) = 0;
  virtual void HookWindowEvent(OsWindowEvent& event) = 0;
};

/// Represents an window in the operating system.
class OsWindow : public ThreadSafeId32EventObject
{
public:
  LightningDeclareType(OsWindow, TypeCopyMode::ReferenceType);

  OsWindow(OsShell* shell,
           StringParam windowName,
           IntVec2Param clientSize,
           IntVec2Param monitorClientPos,
           OsWindow* parentWindow,
           WindowStyleFlags::Enum flags,
           WindowState::Enum state);
  virtual ~OsWindow();

  OsShell* GetShell();

  /// Position of the window's client area in monitor coordinates
  IntVec2 GetMonitorClientPosition();
  void SetMonitorClientPosition(IntVec2Param monitorPosition);

  /// The size of the window including the border
  IntVec2 GetBorderedSize();
  void SetBorderedSize(IntVec2Param borderedSize);

  /// Set the minimum size of the window
  void SetMinClientSize(IntVec2Param minClientSize);

  /// The current client size of the window
  IntVec2 GetClientSize();
  void SetClientSize(IntVec2Param clientSize);

  /// Parent window of this window. Null for Desktop windows.
  OsWindow* GetParent();

  /// Convert screen coordinates to client coordinates
  IntVec2 MonitorToClient(IntVec2Param monitorPosition);

  /// Convert client coordinates to screen coordinates
  IntVec2 ClientToMonitor(IntVec2Param clientPosition);

  /// Style flags control border style, title bar, and other features.
  WindowStyleFlags::Enum GetStyle();
  void SetStyle(WindowStyleFlags::Enum style);

  /// Is the window visible on the desktop?
  bool GetVisible();
  void SetVisible(bool visible);

  /// Set the title of window displayed in the title bar.
  void SetTitle(StringParam title);
  String GetTitle();

  /// State of the Window, Set state to Minimize, Maximize, or Restore the
  /// window
  WindowState::Enum GetState();
  void SetState(WindowState::Enum windowState);

  /// Try to take Focus and bring the window to the foreground.
  /// The OS may prevent this from working if this app is not the foreground
  /// app.
  void TakeFocus();
  /// Does this window have focus?
  bool HasFocus();

  /// Try to close the window. The OsClose event is sent and can be canceled
  void Close();

  /// Destroy the window
  void Destroy();

  /// Capturing the mouse prevents messages from being sent to other windows and
  /// getting mouse movements outside the window (e.g. dragging).
  void SetMouseCapture(bool enabled);

  /// Locks the mouse to prevent it from moving.
  bool GetMouseTrap();
  void SetMouseTrap(bool trapped);
  IntVec2 GetMouseTrapMonitorPosition();
  /// Used to override the trapped position.
  void SetMouseTrapClientPosition(IntVec2 clientPosition, bool useCustomPosition);

  OsHandle GetWindowHandle();

  /// Apply any fixes to the window (after creation) due to driver specific
  /// issues (OpenGl + Intel for example)
  void PlatformSpecificFixup();

  /// Set application progress which may show up in the task bar.
  void SetProgress(ProgressType::Enum progressType, float progress = 0.0f);

  void SendKeyboardEvent(KeyboardEvent& event, bool simulated);
  void SendKeyboardTextEvent(KeyboardTextEvent& event, bool simulated);
  void SendMouseEvent(OsMouseEvent& event, bool simulated);
  void SendMouseDropEvent(OsMouseDropEvent& event, bool simulated);
  void SendWindowEvent(OsWindowEvent& event, bool simulated);

  // If this is set, we must send input events to this
  // first before dispatching them to the rest of the engine.
  OsInputHook* mOsInputHook;

  // Blocks all input generated by the user. Does not block simulated inputs.
  // This is used for running recorded playbacks (such as the PlayUnitTestFile
  // command).
  bool mBlockUserInput;

  // Internal

  void FillKeyboardEvent(Keys::Enum key, KeyState::Enum keyState, KeyboardEvent& keyEvent);
  void FillMouseEvent(IntVec2Param clientPosition, MouseButtons::Enum mouseButton, OsMouseEvent& mouseEvent);

  // ShellWindow interface
  static void ShellWindowOnClose(ShellWindow* window);
  static void ShellWindowOnFocusChanged(bool activated, ShellWindow* window);
  static void ShellWindowOnMouseDropFiles(Math::IntVec2Param clientPosition,
                                          const Array<String>& files,
                                          ShellWindow* window);
  static void ShellWindowOnFrozenUpdate(ShellWindow* window);
  static void ShellWindowOnClientSizeChanged(Math::IntVec2Param clientSize, ShellWindow* window);
  static void ShellWindowOnMinimized(ShellWindow* window);
  static void ShellWindowOnRestored(ShellWindow* window);
  static void ShellWindowOnTextTyped(Rune rune, ShellWindow* window);
  static void ShellWindowOnKeyDown(Keys::Enum key, uint osKey, bool repeated, ShellWindow* window);
  static void ShellWindowOnKeyUp(Keys::Enum key, uint osKey, ShellWindow* window);
  static void ShellWindowOnMouseDown(Math::IntVec2Param clientPosition, MouseButtons::Enum button, ShellWindow* window);
  static void ShellWindowOnMouseUp(Math::IntVec2Param clientPosition, MouseButtons::Enum button, ShellWindow* window);
  static void ShellWindowOnMouseMove(Math::IntVec2Param clientPosition, ShellWindow* window);
  static void ShellWindowOnMouseScrollY(Math::IntVec2Param clientPosition, float scrollAmount, ShellWindow* window);
  static void ShellWindowOnMouseScrollX(Math::IntVec2Param clientPosition, float scrollAmount, ShellWindow* window);
  static void ShellWindowOnDevicesChanged(ShellWindow* window);
  static void ShellWindowOnRawMouseChanged(Math::IntVec2Param movement, ShellWindow* window);
  static WindowBorderArea::Enum ShellWindowOnHitTest(Math::IntVec2Param clientPosition, ShellWindow* window);
  static void ShellWindowOnInputDeviceChanged(
      PlatformInputDevice& device, uint buttons, const Array<uint>& axes, const DataBlock& data, ShellWindow* window);

  // If the mouse is currently trapped (not visible and centered on the window).
  bool mMouseTrapped;

  IntVec2 mCustomMouseTrapClientPosition;
  bool mUseCustomMouseTrapClientPosition;

  // The platform shell window.
  ShellWindow mWindow;
};

// General windows events.
class OsWindowEvent : public Event
{
public:
  LightningDeclareType(OsWindowEvent, TypeCopyMode::ReferenceType);
  OsWindowEvent();

  void Serialize(Serializer& stream);

  OsWindow* Window;
  IntVec2 ClientSize;
};

/// Mouse Events on the main window.
class OsMouseEvent : public Event
{
public:
  LightningDeclareType(OsMouseEvent, TypeCopyMode::ReferenceType);

  OsMouseEvent();
  void Clear();

  OsWindow* Window;
  bool ShiftPressed;
  bool AltPressed;
  bool CtrlPressed;
  IntVec2 ClientPosition;
  Vec2 ScrollMovement;
  bool IsMouseAtTrapPosition;

  // Button For this Event
  MouseButtons::Enum MouseButton;
  byte ButtonDown[MouseButtons::Size];

  void Serialize(Serializer& stream);
};

/// An even that we send when we want to check if we're over a window border
/// gripper such as the title bar for dragging or an edge/corner for resizing.
class OsWindowBorderHitTest : public Event
{
public:
  LightningDeclareType(OsWindowBorderHitTest, TypeCopyMode::ReferenceType);

  OsWindowBorderHitTest();

  OsWindow* Window;
  IntVec2 ClientPosition;

  // This should be set by the receiver of the event.
  WindowBorderArea::Enum mWindowBorderArea;
};

/// Files have been dropped on a OsShellWindow
class OsMouseDropEvent : public OsMouseEvent
{
public:
  LightningDeclareType(OsMouseDropEvent, TypeCopyMode::ReferenceType);
  OsMouseDropEvent()
  {
  }

  void Serialize(Serializer& stream);

  Array<String> Files;
};

} // namespace Plasma