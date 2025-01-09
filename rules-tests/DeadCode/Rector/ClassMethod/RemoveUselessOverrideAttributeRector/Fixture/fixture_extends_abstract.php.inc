<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

abstract class extendsAbstractContract
{
    public function foo(): void{
        echo 'self';
    }
}

final class extendsAbstract extends extendsAbstractContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

abstract class extendsAbstractContract
{
    public function foo(): void{
        echo 'self';
    }
}

final class extendsAbstract extends extendsAbstractContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
?>
