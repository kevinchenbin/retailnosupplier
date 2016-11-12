object frmtuihuoset: Tfrmtuihuoset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #36864#36135#21608#26399#35774#32622
  ClientHeight = 471
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RzPageControl1: TRzPageControl
    Left = 8
    Top = 8
    Width = 409
    Height = 457
    ActivePage = TabSheet1
    DragIndicatorColor = 5263440
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    TabIndex = 0
    TabOrder = 0
    FixedDimension = 23
    object TabSheet1: TRzTabSheet
      Caption = #20379#24212#21830#21608#26399#35774#32622
      object SpeedButton1: TSpeedButton
        Left = 337
        Top = 8
        Width = 49
        Height = 25
        Caption = #20445#23384
        OnClick = SpeedButton1Click
      end
      object Label1: TLabel
        Left = 303
        Top = 15
        Width = 12
        Height = 17
        Caption = #26085
      end
      object Label3: TLabel
        Left = 16
        Top = 16
        Width = 36
        Height = 17
        Caption = #20379#24212#21830
      end
      object editsupplier: TEdit
        Left = 56
        Top = 12
        Width = 57
        Height = 25
        TabOrder = 0
        OnKeyPress = editsupplierKeyPress
      end
      object cbsupplier: TComboBox
        Left = 112
        Top = 12
        Width = 138
        Height = 25
        ItemHeight = 17
        TabOrder = 1
      end
      object RzDBGrid1: TRzDBGrid
        Left = 16
        Top = 39
        Width = 377
        Height = 370
        DataSource = dssupplier
        DefaultDrawing = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        TabOrder = 2
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnCellClick = RzDBGrid1CellClick
        Columns = <
          item
            Expanded = False
            FieldName = 'suppliername'
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830#21517#31216
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clWindowText
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'zhouqi'
            Title.Alignment = taCenter
            Title.Caption = #36864#36135#21608#26399
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clWindowText
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'supplierid'
            Visible = False
          end>
      end
      object editzhouqi: TEdit
        Left = 256
        Top = 12
        Width = 41
        Height = 25
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 3
        Text = '30'
      end
    end
    object TabSheet2: TRzTabSheet
      Caption = #22270#20070#31867#22411#21608#26399#35774#32622
      object SpeedButton2: TSpeedButton
        Left = 337
        Top = 8
        Width = 49
        Height = 25
        Caption = #20445#23384
        OnClick = SpeedButton2Click
      end
      object Label2: TLabel
        Left = 299
        Top = 15
        Width = 12
        Height = 17
        Caption = #26085
      end
      object Label4: TLabel
        Left = 16
        Top = 16
        Width = 24
        Height = 17
        Caption = #31867#21035
      end
      object editclass: TEdit
        Left = 45
        Top = 12
        Width = 64
        Height = 25
        TabOrder = 0
        OnKeyPress = editclassKeyPress
      end
      object cbsupplier2: TComboBox
        Left = 108
        Top = 12
        Width = 138
        Height = 25
        ItemHeight = 17
        TabOrder = 1
      end
      object RzDBGrid2: TRzDBGrid
        Left = 16
        Top = 39
        Width = 377
        Height = 370
        DataSource = dsclass
        DefaultDrawing = True
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        PopupMenu = PopupMenu2
        TabOrder = 2
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnCellClick = RzDBGrid2CellClick
        Columns = <
          item
            Expanded = False
            FieldName = 'classtypename'
            Title.Alignment = taCenter
            Title.Caption = #31867#21035#21517#31216
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'zhouqi'
            Title.Alignment = taCenter
            Title.Caption = #36864#36135#21608#26399
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'classtypeid'
            Visible = False
          end>
      end
      object editzhouqi2: TEdit
        Left = 252
        Top = 12
        Width = 41
        Height = 25
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 3
        Text = '30'
      end
    end
  end
  object dsclass: TDataSource
    DataSet = adotableclass
    Left = 104
    Top = 248
  end
  object adotablesupplier: TADOTable
    Filter = 'type = 1'
    Filtered = True
    TableDirect = True
    TableName = 'SYS_rukuzhouqi'
    Left = 224
    Top = 216
  end
  object adotableclass: TADOTable
    Filter = 'type = 2'
    Filtered = True
    TableDirect = True
    TableName = 'SYS_rukuzhouqi'
    Left = 176
    Top = 152
  end
  object dssupplier: TDataSource
    DataSet = adotablesupplier
    Left = 280
    Top = 168
  end
  object ado: TADOConnection
    LoginPrompt = False
    Left = 360
    Top = 200
  end
  object PopupMenu1: TPopupMenu
    Left = 64
    Top = 168
    object N1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = N1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 280
    Top = 112
    object D1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = D1Click
    end
  end
end
