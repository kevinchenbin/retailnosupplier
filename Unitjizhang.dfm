object frmjizhang: Tfrmjizhang
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #38750#33829#19994#24615#25910#25903
  ClientHeight = 522
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object Label1: TLabel
    Left = 15
    Top = 57
    Width = 48
    Height = 17
    Caption = #26085#26399#36873#25321
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object sbsearch: TSpeedButton
    Left = 172
    Top = 53
    Width = 61
    Height = 24
    Caption = #26597#35810
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    OnClick = sbsearchClick
  end
  object RzPageControl1: TRzPageControl
    Left = 18
    Top = 81
    Width = 508
    Height = 434
    ActivePage = TabSheet1
    DragIndicatorColor = 5263440
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabIndex = 0
    TabOrder = 0
    OnChange = RzPageControl1Change
    FixedDimension = 23
    object TabSheet1: TRzTabSheet
      Caption = #25910#20837
      object Label2: TLabel
        Left = 24
        Top = 368
        Width = 24
        Height = 17
        Caption = #21512#35745
      end
      object dg: TRzDBGrid
        Left = 13
        Top = 3
        Width = 488
        Height = 358
        DataSource = dsa
        DefaultDrawing = True
        Options = [dgEditing, dgAlwaysShowEditor, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        PopupMenu = PopupMenu1
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnColExit = dgColExit
        OnKeyPress = dgKeyPress
        Columns = <
          item
            Expanded = False
            FieldName = 'kemu'
            Title.Alignment = taCenter
            Title.Caption = #31185#30446
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'jimoney'
            Title.Alignment = taCenter
            Title.Caption = #25910#20837
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'department'
            Title.Alignment = taCenter
            Title.Caption = #37096#38376
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'bk'
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 180
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ID'
            Visible = False
          end>
      end
      object editheji: TEdit
        Left = 115
        Top = 367
        Width = 86
        Height = 25
        ReadOnly = True
        TabOrder = 1
      end
    end
    object TabSheet2: TRzTabSheet
      Caption = #25903#20986
      object Label3: TLabel
        Left = 24
        Top = 368
        Width = 24
        Height = 17
        Caption = #21512#35745
      end
      object dgb: TRzDBGrid
        Left = 13
        Top = 4
        Width = 488
        Height = 358
        DataSource = dsb
        DefaultDrawing = True
        Options = [dgEditing, dgAlwaysShowEditor, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        PopupMenu = PopupMenu1
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnColExit = dgbColExit
        OnKeyPress = dgbKeyPress
        Columns = <
          item
            Expanded = False
            FieldName = 'kemu'
            Title.Alignment = taCenter
            Title.Caption = #31185#30446
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'jimoney'
            Title.Alignment = taCenter
            Title.Caption = #25903#20986
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'department'
            Title.Alignment = taCenter
            Title.Caption = #37096#38376
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'bk'
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 180
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ID'
            Visible = False
          end>
      end
      object Edit1: TEdit
        Left = 115
        Top = 368
        Width = 86
        Height = 25
        ReadOnly = True
        TabOrder = 1
      end
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 530
    Height = 36
    AutoResize = False
    AutoStyle = False
    TopMargin = 6
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Color = 16113353
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentFont = False
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnNew
      BtnAlignBottom
      RzToolButton1
      RzToolButton2
      BtnExit)
    object BtnNew: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      Hint = 'New'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 1
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #31185#30446#35774#32622#13'[F2]'
      OnClick = BtnNewClick
    end
    object BtnExit: TRzToolButton
      Left = 254
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 64
      Top = 0
      Width = 70
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 9
      GradientColorStyle = gcsSystem
      ImageIndex = 8
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20445#23384#13'(&S)'
      OnClick = BtnAlignBottomClick
    end
    object RzToolButton1: TRzToolButton
      Left = 134
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'(&P)'
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 194
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272#13'(&Y)'
      OnClick = RzToolButton2Click
    end
  end
  object dtpdate: TRzDateTimePicker
    Left = 70
    Top = 51
    Width = 99
    Height = 25
    Date = 41065.418178946760000000
    Time = 41065.418178946760000000
    TabOrder = 2
  end
  object ADOConnection1: TADOConnection
    Left = 552
    Top = 280
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 688
    Top = 224
  end
  object aq2: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      
        'select a.department,a.bk,jimoney,kemuname,a.id from dbo.FN_jizha' +
        'ng a left join FN_Kemu b on a.kemuid=b.id where moneytype=2 and ' +
        'datediff(d,'#39'2013-03-05'#39',getdate())=0')
    Left = 336
    Top = 232
  end
  object aqb: TADOQuery
    Parameters = <>
    Left = 88
    Top = 368
  end
  object frxjizhang: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41067.418635057900000000
    ReportOptions.LastChange = 41341.661916412030000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnGetValue = frxjizhangGetValue
    Left = 408
    Top = 280
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 408
    Top = 200
  end
  object dsa: TDataSource
    DataSet = aqa
    Left = 104
    Top = 224
  end
  object dsb: TDataSource
    DataSet = aqb
    Left = 128
    Top = 376
  end
  object aqa: TADOQuery
    Parameters = <>
    Left = 160
    Top = 264
  end
  object PopupMenu1: TPopupMenu
    Left = 280
    Top = 232
    object D1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = D1Click
    end
  end
  object frxdb: TfrxDBDataset
    UserName = 'frxdb'
    CloseDataSource = False
    Left = 200
    Top = 128
  end
end
