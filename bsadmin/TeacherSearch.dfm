object frmteachersearch: Tfrmteachersearch
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #25945#24072#36820#28857#32479#35745
  ClientHeight = 548
  ClientWidth = 801
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 42
    Width = 785
    Height = 71
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label4: TLabel
      Left = 586
      Top = 21
      Width = 14
      Height = 20
      Caption = #21040
    end
    object cbteacher: TComboBoxEx
      Left = 182
      Top = 21
      Width = 146
      Height = 29
      ItemsEx = <>
      ItemHeight = 16
      TabOrder = 2
    end
    object editname: TEdit
      Left = 84
      Top = 21
      Width = 92
      Height = 28
      TabOrder = 0
      OnKeyPress = editnameKeyPress
    end
    object dtpbegin: TDateTimePicker
      Left = 461
      Top = 21
      Width = 119
      Height = 28
      Date = 41841.604656099540000000
      Time = 41841.604656099540000000
      TabOrder = 3
    end
    object dtpend: TDateTimePicker
      Left = 619
      Top = 21
      Width = 121
      Height = 28
      Date = 41841.604746296300000000
      Time = 41841.604746296300000000
      TabOrder = 4
    end
    object cteacher: TCheckBox
      Left = 5
      Top = 26
      Width = 73
      Height = 17
      Caption = #25945#24072#22995#21517
      TabOrder = 5
    end
    object CheckBox2: TCheckBox
      Left = 373
      Top = 26
      Width = 80
      Height = 17
      Caption = #38144#21806#26085#26399
      TabOrder = 1
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 801
    Height = 36
    AutoResize = False
    AutoStyle = False
    TopMargin = 6
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderColor = clSkyBlue
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
    GradientColorStyle = gcsCustom
    ParentFont = False
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      Btn
      BtnExit
      RzToolButton2)
    object BtnExit: TRzToolButton
      Left = 64
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'(&M)'
      Visible = False
      OnClick = BtnExitClick
    end
    object Btn: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      DisabledIndex = 5
      GradientColorStyle = gcsSystem
      ImageIndex = 4
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'(&A)'
      OnClick = BtnClick
    end
    object RzToolButton2: TRzToolButton
      Left = 124
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = RzToolButton2Click
    end
  end
  object dbgrid: TDBGridEh
    Left = 8
    Top = 136
    Width = 785
    Height = 404
    Ctl3D = False
    DataSource = DataSource1
    Flat = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -11
    FooterFont.Name = 'Tahoma'
    FooterFont.Style = []
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    SumList.Active = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = dbgridDblClick
    Columns = <
      item
        EditButtons = <>
        FieldName = 'teacherid'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
      end
      item
        EditButtons = <>
        FieldName = 'name'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #22995#21517
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'class'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #29677#32423
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'kemu'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #31185#30446
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'tel'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #30005#35805
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
      end
      item
        EditButtons = <>
        FieldName = 'fdvalue'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #36820#28857
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -14
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
      end>
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 432
    Top = 296
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 352
    Top = 280
  end
  object sd: TSaveDialog
    DefaultExt = 'xls'
    Filter = 'Excel|*.xls'
    Left = 440
    Top = 208
  end
  object aqq: TADOQuery
    Parameters = <>
    Left = 296
    Top = 240
  end
  object ADODataSet1: TADODataSet
    Parameters = <>
    Left = 200
    Top = 248
  end
  object adosp: TADOStoredProc
    ProcedureName = 'TeacherFDSearch'
    Parameters = <
      item
        Name = '@teacherid'
        Size = -1
        Value = Null
      end
      item
        Name = '@begintime'
        Size = -1
        Value = Null
      end
      item
        Name = '@endtime'
        Size = -1
        Value = Null
      end>
    Left = 168
    Top = 328
  end
end
