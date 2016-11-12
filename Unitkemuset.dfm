object frmkemuset: Tfrmkemuset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #31185#30446#35774#32622
  ClientHeight = 306
  ClientWidth = 388
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 10
    Top = 61
    Width = 48
    Height = 17
    Caption = #31185#30446#21517#31216
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 202
    Top = 61
    Width = 24
    Height = 17
    Caption = #31867#22411
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 89
    Width = 367
    Height = 200
    DataSource = DataSource1
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = DBGrid1CellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'id'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'kemuname'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #21517#31216
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 160
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'type1'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #31867#22411
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end>
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 388
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
      BtnExit
      RzToolButton1)
    object BtnNew: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      Hint = 'New'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #28155#21152#13'[&A]'
      OnClick = BtnNewClick
    end
    object BtnExit: TRzToolButton
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
      Caption = #20445#23384#13'(&Q)'
      Enabled = False
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
      Caption = #20462#25913#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object RzToolButton1: TRzToolButton
      Left = 194
      Top = 0
      Width = 60
      Height = 36
      Hint = 'New'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21024#38500#13'[&D]'
      OnClick = RzToolButton1Click
    end
  end
  object editkemuname: TEdit
    Left = 64
    Top = 58
    Width = 121
    Height = 25
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object cbtype: TComboBox
    Left = 232
    Top = 58
    Width = 145
    Height = 25
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ItemHeight = 17
    ItemIndex = 0
    ParentFont = False
    TabOrder = 3
    Text = #25910#20837
    Items.Strings = (
      #25910#20837
      #25903#20986)
  end
  object aq: TADOQuery
    Parameters = <>
    SQL.Strings = (
      
        'select *,case a.type when 1 then '#39#25910#20837#39' when 2 then '#39#25903#20986#39' end as ty' +
        'pe1 from dbo.FN_kemu a ')
    Left = 224
    Top = 192
  end
  object DataSource1: TDataSource
    DataSet = aq
    Left = 312
    Top = 240
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 288
    Top = 168
  end
end
