object frmteacherFD: TfrmteacherFD
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #25945#24072#36820#28857#35774#32622
  ClientHeight = 581
  ClientWidth = 810
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 810
    Height = 581
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    ShowCaption = False
    TabOrder = 0
    object Label1: TLabel
      Left = 40
      Top = 48
      Width = 27
      Height = 17
      Caption = #22995#21517':'
    end
    object l1: TLabel
      Left = 392
      Top = 96
      Width = 27
      Height = 17
      Caption = #36820#28857':'
    end
    object Label3: TLabel
      Left = 562
      Top = 96
      Width = 51
      Height = 17
      Caption = #36820#28857#37329#39069':'
    end
    object Label2: TLabel
      Left = 370
      Top = 48
      Width = 48
      Height = 17
      Caption = #26377#25928#26399#20174
    end
    object Label4: TLabel
      Left = 562
      Top = 48
      Width = 12
      Height = 17
      Caption = #21040
    end
    object lblCatalog: TLabel
      Left = 47
      Top = 96
      Width = 24
      Height = 17
      Caption = #20070#21495
      Color = clHighlight
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
    end
    object Label5: TLabel
      Left = 544
      Top = 94
      Width = 11
      Height = 17
      Caption = '%'
    end
    object editname: TEdit
      Left = 77
      Top = 45
      Width = 92
      Height = 25
      TabOrder = 0
      OnKeyPress = editnameKeyPress
    end
    object cbteacher: TComboBoxEx
      Left = 175
      Top = 45
      Width = 146
      Height = 26
      ItemsEx = <>
      ItemHeight = 16
      TabOrder = 1
      OnChange = cbteacherChange
    end
    object DBGrid1: TDBGrid
      Left = 16
      Top = 152
      Width = 777
      Height = 401
      DataSource = DataSource1
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      PopupMenu = PopupMenu1
      TabOrder = 2
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnCellClick = DBGrid1CellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'ID'
          Title.Alignment = taCenter
          Title.Caption = #24207#21495
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'isbn'
          Title.Alignment = taCenter
          Title.Caption = 'ISBN'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'abbreviatedname'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'discount'
          Title.Alignment = taCenter
          Title.Caption = #36820#28857'%'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'disvalue'
          Title.Alignment = taCenter
          Title.Caption = #36820#28857#20540
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'begindate'
          Title.Alignment = taCenter
          Title.Caption = #24320#22987#26085#26399
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'enddate'
          Title.Alignment = taCenter
          Title.Caption = #32467#26463#26085#26399
          Width = 69
          Visible = True
        end>
    end
    object dtpbegin: TDateTimePicker
      Left = 432
      Top = 48
      Width = 119
      Height = 25
      Date = 41841.604656099540000000
      Time = 41841.604656099540000000
      TabOrder = 3
    end
    object dtpend: TDateTimePicker
      Left = 627
      Top = 46
      Width = 121
      Height = 25
      Date = 41841.604746296300000000
      Time = 41841.604746296300000000
      TabOrder = 4
    end
    object edtCatalog: TEdit
      Left = 77
      Top = 94
      Width = 244
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 5
      OnKeyPress = edtCatalogKeyPress
    end
    object numerfd: TRzNumericEdit
      Left = 432
      Top = 93
      Width = 105
      Height = 25
      TabOrder = 6
      OnKeyPress = numerfdKeyPress
      IntegersOnly = False
      DisplayFormat = '##0.00'
    end
    object numerfdje: TRzNumericEdit
      Left = 627
      Top = 93
      Width = 121
      Height = 25
      TabOrder = 7
      OnKeyPress = numerfdjeKeyPress
      IntegersOnly = False
      DisplayFormat = '##0.00'
    end
    object RzToolbar1: TRzToolbar
      Left = 2
      Top = 2
      Width = 806
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
      TabOrder = 8
      VisualStyle = vsClassic
      ToolbarControls = (
        Btn
        RzToolButton2)
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
        Caption = #20445#23384#13'(&S)'
        OnClick = BtnClick
      end
      object RzToolButton2: TRzToolButton
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
        Caption = #36864#20986#13'(&Q)'
        OnClick = RzToolButton2Click
      end
    end
  end
  object PM: TPopupMenu
    Left = 48
    Top = 328
    object N1: TMenuItem
      Caption = #20070'  '#21495
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #33258#32534#30721
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #20070'  '#21517
      OnClick = N3Click
    end
    object N6: TMenuItem
      Caption = #23450'  '#20215
      OnClick = N6Click
    end
    object N4: TMenuItem
      Caption = #20316'  '#32773
      OnClick = N4Click
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 368
    Top = 224
  end
  object dbgridadoquery: TADOQuery
    Parameters = <
      item
        Name = 'teacherid'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      
        'select a.id,a.catalogid,a.discount,a.disvalue,a.begindate,a.endd' +
        'ate,b.isbn,b.name,b.author,'
      
        'b.userdefcode,b.price,p.abbreviatedname from dbo.BS_TeacherFD a ' +
        'left join dbo.BS_BookCatalog b on b.id = a.catalogid'
      
        'left join dbo.BS_PressInfo p on p.id = b.pressid left join dbo.B' +
        'S_BookType c on c.id = b.bigbooktypeid'
      'where teacherid=:teacherid')
    Left = 144
    Top = 272
  end
  object DataSource1: TDataSource
    DataSet = dbgridadoquery
    Left = 368
    Top = 296
  end
  object PopupMenu1: TPopupMenu
    Left = 496
    Top = 280
    object D1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = D1Click
    end
  end
end
