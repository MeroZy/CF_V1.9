
Imports System
Imports System.ComponentModel
Imports System.IO
Imports System.Text
Imports System.Net
Public Class Form1
    Dim TestPos As Integer
    Dim Generator As System.Random = New System.Random()
    Dim randomvalue As Single
    Dim TestPos1 As Integer
    Dim Generator1 As System.Random = New System.Random()
    Dim randomvalue1 As Single
    Dim ExeName As String = IO.Path.GetFileNameWithoutExtension(Application.ExecutablePath)
    Public WithEvents download As WebClient
    Private Sub Timer1_Tick(sender As Object, e As EventArgs)
        FlatProgressBar1.Increment(5)
    End Sub

    Private Sub VButton2_Click(sender As Object, e As EventArgs)
        If FlatComboBox1.Text = "CrossFire West [Windows 7,8,10]" Then
            Dim SourcePath As String = "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll"  'This is just an example string and could be anything, it maps to fileToCopy in your code."
            Dim SaveDirectory As String = "C:\Program Files\Microsoft .NET"

            Dim Filename As String = System.IO.Path.GetFileName(SourcePath) 'get the filename of the original file without the directory on it
            Dim SavePath As String = System.IO.Path.Combine(SaveDirectory, Filename) 'combines the saveDirectory and the filename to get a fully qualified path.
            Try
                If System.IO.File.Exists(SavePath) Then
                    If (Not System.IO.Directory.Exists("C:\Program Files\Microsoft .NET\")) Then
                        System.IO.Directory.CreateDirectory("C:\Program Files\Microsoft .NET\")
                    End If
                    My.Computer.FileSystem.DeleteFile("C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    download = New WebClient
                    download.DownloadFileAsync(New Uri(Label5.Text), "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    Timer9.Start()
                    VButton2.BackColor = Color.Orange
                    VButton2.Text = "Loading"
                    VButton2.Enabled = False
                    FlatAlertBox1.Hide()
                Else
                    If (Not System.IO.Directory.Exists("C:\Program Files\Microsoft .NET\")) Then
                        System.IO.Directory.CreateDirectory("C:\Program Files\Microsoft .NET\")
                    End If
                    download = New WebClient
                    download.DownloadFileAsync(New Uri(Label5.Text), "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    Timer9.Start()
                    VButton2.BackColor = Color.Orange
                    VButton2.Text = "Loading"
                    VButton2.Enabled = False
                    FlatAlertBox1.Hide()
                End If
            Catch
                Interaction.MsgBox("Error on load hack", MsgBoxStyle.Critical, Nothing)
                FlatAlertBox1.Show()
                FlatAlertBox1.kind = FlatAlertBox._Kind.Error
                FlatAlertBox1.Text = "Error please restart the application"

            End Try
            'غير معدل
        ElseIf FlatComboBox1.Text = "CrossFire NA + Menu [Windows 7]" Then
            Dim SourcePath As String = "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll"  'This is just an example string and could be anything, it maps to fileToCopy in your code."
            Dim SaveDirectory As String = "C:\Program Files\Microsoft .NET"

            Dim Filename As String = System.IO.Path.GetFileName(SourcePath) 'get the filename of the original file without the directory on it
            Dim SavePath As String = System.IO.Path.Combine(SaveDirectory, Filename) 'combines the saveDirectory and the filename to get a fully qualified path.
            Try
                If System.IO.File.Exists(SavePath) Then
                    If (Not System.IO.Directory.Exists("C:\Program Files\Microsoft .NET\")) Then
                        System.IO.Directory.CreateDirectory("C:\Program Files\Microsoft .NET\")
                    End If
                    My.Computer.FileSystem.DeleteFile("C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    download = New WebClient
                    download.DownloadFileAsync(New Uri(Label5.Text), "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    Timer9.Start()
                    VButton2.BackColor = Color.Orange
                    VButton2.Text = "Loading"
                    VButton2.Enabled = False
                Else
                    If (Not System.IO.Directory.Exists("C:\Program Files\Microsoft .NET\")) Then
                        System.IO.Directory.CreateDirectory("C:\Program Files\Microsoft .NET\")
                    End If
                    download = New WebClient
                    download.DownloadFileAsync(New Uri(Label5.Text), "C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                    Timer9.Start()
                    VButton2.BackColor = Color.Orange
                    VButton2.Text = "Loading"
                    VButton2.Enabled = False
                End If
            Catch
                Interaction.MsgBox("Error on load hack", MsgBoxStyle.Critical, Nothing)
                End
            End Try
        Else
            Interaction.MsgBox("Please Select Server !", MsgBoxStyle.Information, Nothing)
        End If

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer7.Interval = 100
        Timer5.Interval = 100
        Dim P As New WebClient

        FlatComboBox1.Text = "CrossFire West [Windows 7,8,10]"
        Try
            Label11.Text = P.DownloadString("https://textuploader.com/dzzbf/raw") 'Message
            Label2.Text = P.DownloadString("https://textuploader.com/1q2yy/raw") 'online 
            'Label10.Text = P.DownloadString("https://textuploader.com/dzzb7/raw") 'link na+auto اخنياري للاحتياط
            Label5.Text = P.DownloadString("https://textuploader.com/1q2ye/raw") 'link الي بمنيو

            If Label2.Text = "Online" Then
                Label2.ForeColor = Color.Green
                Label1.Text = "..."
                Timer1.Interval = 50
                Timer4.Start()
                Timer5.Start()
                FlatAlertBox1.Show()
                Dim f As New IO.FileInfo("C:\Windows\System32\msvcr100d.dll")

                If Not f.Exists Then
                    IO.File.WriteAllBytes("C:\Windows\System32" & "\msvcr100d.dll", My.Resources.msvcr100d)


                Else

                End If
            Else
                Label2.ForeColor = Color.Red
                Process.Start("www.youtube.com/channel/UC-18IvrIacu-nduN35MsQuA")
                Try
                    My.Computer.FileSystem.DeleteFile("C:\Windows\System32\kyfguiCuGb3sN7Vix8.dll")
                Catch

                End Try
                Interaction.MsgBox("Hack Is Offline Please Go to Our Channels For New Update", MsgBoxStyle.Critical, Nothing)

                End
            End If
        Catch
            Interaction.MsgBox("Error to connect to the internet", MsgBoxStyle.Critical, Nothing)
            End
        End Try
        Try
            IO.File.WriteAllBytes(My.Computer.FileSystem.SpecialDirectories.AllUsersApplicationData & "\Luncher.exe", My.Resources.Lunch)
        Catch
            Interaction.MsgBox("Turn off your antivires and try again", MsgBoxStyle.Critical, Nothing)
            End
        End Try

    End Sub

    Private Sub Timer1_Tick_1(sender As Object, e As EventArgs)
        FlatComboBox1.Enabled = False
        Dim TargetProcess As Process() = Process.GetProcessesByName(FlatTextBox1.Text)
        If TargetProcess.Length = 0 Then
            Me.Label1.Text = ("Waiting for " + FlatTextBox1.Text + ".exe")
            FlatAlertBox1.Show()
            FlatAlertBox1.Text = "Start CF Now"
            FlatAlertBox1.kind = FlatAlertBox._Kind.Info
            Label1.ForeColor = Color.Green
            VButton2.Text = "Hack Loaded"
            VButton2.BackColor = Color.Green
            VButton2.Enabled = False
            VButton2.Cursor = Cursors.Default

        Else
            Timer1.Stop()
            IO.File.WriteAllBytes("C:\Program Files\Microsoft .NET\pQ5zrihFh6H52gjoxS5Q6Cup.exe", My.Resources.dwz48d43w1w156wdwm)

            '*Dim path As String = My.Computer.FileSystem.SpecialDirectories.AllUsersApplicationData & "\Luncher.bat"
            ' Create a file to write to. 
            'Using sw As StreamWriter = File.CreateText(path)
            'sw.Write(My.Resources.Lunch)
            'End Using
            Me.Label1.Text = "Successfully Injected!"
            Me.Label1.ForeColor = Color.Green
            FlatAlertBox1.Text = "Successfully Injected"
            FlatAlertBox1.kind = FlatAlertBox._Kind.Success
            Timer2.Start()

        End If
    End Sub

    Private Sub Timer2_Tick(sender As Object, e As EventArgs)
        ProgressBar1.Increment(2)
        If ProgressBar1.Value = 50 Then
            If FlatComboBox1.Text = "CrossFire NA + Menu [Windows 7]" Then
                Dim psi As New ProcessStartInfo(My.Computer.FileSystem.SpecialDirectories.AllUsersApplicationData & "\Luncher.bat")
                psi.RedirectStandardError = True
                psi.RedirectStandardOutput = True
                psi.CreateNoWindow = False
                psi.WindowStyle = ProcessWindowStyle.Hidden
                psi.UseShellExecute = False

                Dim process As Process = process.Start(psi)

            ElseIf FlatComboBox1.Text = "CrossFire West [Windows 7,8,10]" Then
                Try
                    Process.Start(My.Computer.FileSystem.SpecialDirectories.AllUsersApplicationData & "\Luncher.exe")
                Catch
                    Interaction.MsgBox("Turn off your antivires and try again", MsgBoxStyle.Critical, Nothing)
                    End
                End Try

            End If


        End If
        If ProgressBar1.Value = 100 Then
            Timer2.Stop()
            Process.Start("https://www.youtube.com/channel/UC-18IvrIacu-nduN35MsQuA?sub_confirmation=1")
            Process.Start("https://www.youtube.com/channel/UCHHeBs3XA517ba4BLYHXpIw?sub_confirmation=1")
            Process.Start("https://www.youtube.com/channel/UCBfGPLXGrL3LgcTN4m-1j-g?sub_confirmation=1")

            End
        End If
    End Sub

    Private Sub Timer4_Tick(sender As Object, e As EventArgs)
        Try
            Me.Timer4.Stop()
            Me.randomvalue = Me.Generator.Next(1, 11)
            Interaction.MsgBox("Locked, Skip Ad 1/2 to Unlock !", MsgBoxStyle.Information, Nothing)
            Label7.Text = "Skip Ad 1 of 2"
            Label7.ForeColor = Color.Red
            Me.Timer5.Start()
            If (Me.randomvalue = 1) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fm")
            End If
            If (Me.randomvalue = 2) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fo")
            End If
            If (Me.randomvalue = 3) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fq")
            End If
            If (Me.randomvalue = 4) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fr")
            End If
            If (Me.randomvalue = 5) Then
                Process.Start("chrome.exe", "http://gsul.me/b9ft")
            End If
            If (Me.randomvalue = 6) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fy")
            End If
            If (Me.randomvalue = 7) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fz")
            End If
            If (Me.randomvalue = 8) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fA")
            End If
            If (Me.randomvalue = 9) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fC")
            End If
            If (Me.randomvalue = 10) Then
                Process.Start("chrome.exe", "http://gsul.me/b9fE")
            End If
        Catch
            Interaction.MsgBox("Please install the latest verson of Google Chrome", MsgBoxStyle.Critical, Nothing)
            Process.Start("https://www.google.com/chrome/")
            End
        End Try

    End Sub

    Private Sub Timer5_Tick(sender As Object, e As EventArgs)
        Dim process As Process
        For Each process In process.GetProcesses
            If (process.ProcessName = "chrome") Then
                If (Me.randomvalue = 1) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "101010.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 2) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "202020.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 3) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "303030.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 4) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "404040.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 5) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "505050.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 6) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "606060.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 7) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "707070.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 8) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "808080.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 9) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "909090.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue = 10) Then
                    Me.TestPos = Strings.InStr(process.MainWindowTitle, "100100100.txt", CompareMethod.Binary)
                End If
                If (Me.TestPos > 0) Then
                    Me.Timer5.Stop()
                    Me.TopMost = True
                    Interaction.MsgBox("Skip Ad 2/2", MsgBoxStyle.Information, Nothing)
                    Me.Timer5.Stop()
                    Timer6.Start()

                End If
            End If
        Next
    End Sub

    Private Sub Timer6_Tick(sender As Object, e As EventArgs)
        Me.Timer6.Stop()
        Me.randomvalue1 = Me.Generator1.Next(1, 11)
        Label7.Text = "Skip Ad 2 of 2"
        Label7.ForeColor = Color.Red
        Me.Timer7.Start()
        If (Me.randomvalue1 = 1) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvO")
        End If
        If (Me.randomvalue1 = 2) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvM")
        End If
        If (Me.randomvalue1 = 3) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvK")
        End If
        If (Me.randomvalue1 = 4) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvI")
        End If
        If (Me.randomvalue1 = 5) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvH")
        End If
        If (Me.randomvalue1 = 6) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvF")
        End If
        If (Me.randomvalue1 = 7) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvD")
        End If
        If (Me.randomvalue1 = 8) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvA")
        End If
        If (Me.randomvalue1 = 9) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvv")
        End If
        If (Me.randomvalue1 = 10) Then
            Process.Start("chrome.exe", "https://gsurl.be/hmvu")
        End If
    End Sub

    Private Sub Timer7_Tick(sender As Object, e As EventArgs)
        Dim process As Process
        For Each process In process.GetProcesses
            If (process.ProcessName = "chrome") Then
                If (Me.randomvalue1 = 1) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "100100100.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 2) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "909090.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 3) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "606060.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 4) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "707070.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 5) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "808080.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 6) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "303030.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 7) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "404040.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 8) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "505050.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 9) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "202020.txt", CompareMethod.Binary)
                End If
                If (Me.randomvalue1 = 10) Then
                    Me.TestPos1 = Strings.InStr(process.MainWindowTitle, "101010.txt", CompareMethod.Binary)
                End If
                If (Me.TestPos1 > 0) Then
                    VButton2.Enabled = True
                    VButton2.BackColor = Color.Orange
                    VButton2.Text = "UnLocked | Load Hack!"
                    Label7.Text = "Ads Skipped Successfully"
                    Label7.ForeColor = Color.Green
                    Me.Timer7.Stop()
                    Me.VButton2.Enabled = True
                    Me.TopMost = True
                    Interaction.MsgBox("Unlocked ! Select Server :D", MsgBoxStyle.Information, Nothing)
                    VButton2.Cursor = Cursors.Hand
                    Me.Timer6.Stop()
                    FlatAlertBox1.Show()
                    FlatAlertBox1.kind = FlatAlertBox._Kind.Info
                    FlatAlertBox1.Text = "Select Server :D "
                    FlatComboBox1.Enabled = True
                End If
            End If
        Next
    End Sub

    Private Sub Timer8_Tick(sender As Object, e As EventArgs)
        ProgressBar1.Increment(2)
        If ProgressBar1.Value = 50 Then


        End If
        If ProgressBar1.Value = 100 Then
            Timer2.Stop()
            Process.Start("https://www.youtube.com/channel/UC-18IvrIacu-nduN35MsQuA?sub_confirmation=1")


            End
        End If
    End Sub
    Private Sub WC_DownloadProgressChanged(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs) Handles download.DownloadProgressChanged
        FlatProgressBar1.Value = e.ProgressPercentage
    End Sub

    Private Sub Timer9_Tick(sender As Object, e As EventArgs)
        If FlatProgressBar1.Value = 100 Then
            Timer9.Stop()
            Timer1.Start()
        End If
    End Sub

    Private Sub LinkLabel1_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs)
        Process.Start("https://www.youtube.com/channel/UCHHeBs3XA517ba4BLYHXpIw")
    End Sub

    Private Sub LinkLabel2_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs)
        Process.Start("https://www.youtube.com/channel/UC-18IvrIacu-nduN35MsQuA")
    End Sub

End Class
